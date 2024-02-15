# Implementar notificações RSS no Google Chat

Para isso precisaremos criar uma planilha, que receberá as notificações, e que em seguida publique-as no google canal chat via WebHook.

## Criar um Space no Google Chat

Primeiro crie o chat (space) onde seu Boot irá publicar as notificações.
Faça-o acessando `chat.google.com` ou atravéz do gmail mesmo, e clicando em **Novo Chat** > **Criar Espaço**. 

## Criar um WebHook no seu espaço

Acesse as configurações do seu espaço no google chat -> **Apps e Integrações** > **WebHooks** > **Adicionar Webhooks**.

Dê um nome e um ícone ao seu webhook;

Salve e copie a URL dele.

## Criar um appscript

Acesse o [Google AppScript](https://script.google.com) e crie um novo projeto;

Cole o seguinte código no projeto:

```js
var DEBUG = false;

var RESET_LAST_LOOKUP_TIME = 'Sun Jan 16 00:00:00 GMT-05:00 2022';  // Format: Fri Dec 10 14:37:12 GMT-05:00 2021
var feeds = [
    {
        name:"ABNT News",
        url:"https://abnt.org.br/feed/atom/",
        type:"ATOM",
        themeLogo:"https://www.abntcatalogo.com.br/assets/imgs/theme/logo.png",
        webhook:"https://chat.googleapis.com/v1/spaces/AAAAfINdsv/messages?key=AIzaSyDdI0hCZtE6eaedcevySjMm-WEfRq3CPzqKqqsHI&token=BnllJxpWgwrvwevqhJvO4BdTMld0AglPzEI",
        active:true
    },
    {
        name:"KingHost Status",
        url:"https://status.kinghost.net.br/history.atom",
        type:"ATOM",
        themeLogo:"https://dka575ofm4ao0.cloudfront.net/pages-transactional_logos/retina/27219/01A-kinghost-PRERENCIAL-roxo.png",
        webhook:"https://chat.googleapis.com/v1/spaces/AAAAfINdsv/messages?key=AIzaSyDdI0hCZtE6eaedcevySjMm-WEfRq3CPzqKqqsHI&token=BnllJxpWgwrvwevqhJvO4BdTMld0AglPzEI",
        active:true
    }
]

/*
* DO NOT CHANGE ANYTHING BELOW THIS LINE
*/

// only use this if you want to reset the time back to the specified time
function job_reset_last_lookup_time() {
  var getcurrentUpdateTime = new Date(parseFloat(PropertiesService.getScriptProperties().getProperty("lastUpdate")) || 0);
  Logger.log('Current Update time is: ' + getcurrentUpdateTime);
  PropertiesService.getScriptProperties().setProperty("lastUpdate", new Date(RESET_LAST_LOOKUP_TIME).getTime());
  var getnewUpdateTime = new Date(parseFloat(PropertiesService.getScriptProperties().getProperty("lastUpdate")) || 0);
  Logger.log('New Update time is: ' + getnewUpdateTime);
}

// loop through all the filtered rows (the active ones)
function job_fetch_all_feeds() {

  feeds.forEach(function(item, index) {
    
    if(item.active){
        fetchNews_(item.name, item.url, item.type, item.themeLogo, item.webhook);
    }

  });

  var now = new Date();
  PropertiesService.getScriptProperties().setProperty("lastUpdate", now.getTime());
  Logger.log('Last Update Setting to: ' + now);
  var getnewUpdateTime = new Date(parseFloat(PropertiesService.getScriptProperties().getProperty("lastUpdate")) || 0);
  Logger.log('Last Update Time is:' + getnewUpdateTime);

}

// fetch a feed, and send any new events through to the associated Chat room
function fetchNews_(FEED_NAME, FEED_URL, FEED_TYPE, FEED_LOGO_URL, WEBHOOK_URL) {
  
  var lastUpdate = new Date(parseFloat(PropertiesService.getScriptProperties().getProperty("lastUpdate")) || 0);

  Logger.log("Last update: " + lastUpdate);
  
  Logger.log("Fetching '" + FEED_NAME + "'...");
  
  try{
    var xml = UrlFetchApp.fetch(FEED_URL).getContentText();
    var document = XmlService.parse(xml);
  }
  catch(err){
    Logger.log(err);
  }
  if(FEED_TYPE == "RSS") {

    Logger.log("RSS Feed being parsed - " + FEED_NAME);
    try{
      var items = document.getRootElement().getChild('channel').getChildren('item').reverse();
    }
    catch(err){
      Logger.log(err);
    }
    Logger.log(items.length + " entrie(s) found");
    
    var count = 0;
    
    for (var i = 0; i < items.length; i++) {

      try{
        var pubDate = new Date(items[i].getChild('pubDate').getText());
        var title = items[i].getChild("title").getText();
        var description = items[i].getChild("description").getText();
        var link = items[i].getChild("link").getText();
        var eventDate = items[i].getChild("pubDate").getText();
      }
      catch(err){
        Logger.log(err);
      }
      if (description == null){
        description = "No description available."
      }
      // check to make sure the feed event is after the last time we ran the script
      if(pubDate.getTime() > lastUpdate.getTime()) {
        //Logger.log("Logging Event - Title: " + title + " | Date: " + eventDate + " | Link: " + link);
        if(!DEBUG){
          postTopicAsCard_(WEBHOOK_URL, FEED_NAME, FEED_URL, FEED_LOGO_URL, title, eventDate, description, link);
        }
        else{
          Logger.log(pubDate);
          Logger.log(pubDate.getTime());
          Logger.log(title);
          Logger.log(link);
          Logger.log(description);
          Logger.log("--------------------");
        }
        
        count++;
      }
    }

  } else {
    //must be ATOM then
    Logger.log("ATOM Feed being parsed - " + FEED_NAME);

    var url = FEED_URL;
    var xml = UrlFetchApp.fetch(url).getContentText();
    var document = XmlService.parse(xml);
    var root = document.getRootElement();
    var atom = XmlService.getNamespace('http://www.w3.org/2005/Atom');

    var entries = root.getChildren('entry', atom);
    var count = 0;
    for (var i = 0; i < entries.length; i++) {
      try{
        var title = entries[i].getChild('title', atom).getText();
        var pubDate = new Date(entries[i].getChild('updated', atom).getText());
        var link = entries[i].getChild("link", atom).getAttribute('href').getValue();
        var eventDate = entries[i].getChild("updated", atom).getText();
      }
      catch(err){
        Logger.log(err);
      }
      
      // check to make sure the feed event is after the last time we ran the script
      if(pubDate.getTime() > lastUpdate.getTime()) {
        //Logger.log("Logging Event - Title: " + title + " | Date: " + eventDate + " | Link: " + link);
        if(!DEBUG){
          postTopicAsCard_(WEBHOOK_URL, FEED_NAME, FEED_URL, FEED_LOGO_URL, title, eventDate, title, link);
        }
        else{
          Logger.log(pubDate);
          Logger.log(pubDate.getTime());
          Logger.log(title);
          Logger.log(link);
          Logger.log("--------------------");
        }
        count++;
      }

    }

    Logger.log(entries.length + " entrie(s) found");
    Logger.log("--> " + count + " item(s) posted");
  }
  
}

// quick function to take the info, send it to create a card, and then post the card.
function postTopicAsCard_(webhook_url, feed_name, feed_url, feed_logo_url, card_title, card_subtitle, card_description, card_link) {
  
  var card_json = createCardJson_(feed_name, feed_url, feed_logo_url, card_title, card_subtitle, card_description, card_link);

  // set options for what will be sent to Chat according to documentation
  var options = {
    'method' : 'post',
    'contentType': 'application/json',
    'payload' : JSON.stringify(card_json)
  };
  try{
    UrlFetchApp.fetch(webhook_url, options);
  }
  catch(err){
    Logger.log(err);
  }
}

/**
 * Creates a card-formatted response.
  * @return {object} JSON-formatted response
 */
function createCardJson_(feed_name, feed_url, feed_logo_url, card_title, card_subtitle, card_description, card_link) {
  return {
    "cards": [
    {
      "header": {
        "title": feed_name,
        "subtitle": feed_url,
        "imageUrl": feed_logo_url
      },
      "sections": [
        {
          "widgets": [
              {
                "keyValue": {
                  "topLabel": "New Post",
                  "content": card_title,
                  "contentMultiline": "true",
                  "icon": "BOOKMARK",
                  "bottomLabel": card_subtitle
                }
              },
              {
                "keyValue": {
                  "topLabel": "Description",
                  "content": card_description,
                  "contentMultiline": "true",
                  "icon": "DESCRIPTION"
                }
              }
            ]
        },
        {
          "widgets": [
              {
                  "buttons": [
                    {
                      "textButton": {
                        "text": "OPEN LINK",
                        "onClick": {
                          "openLink": {
                            "url": card_link
                          }
                        }
                      }
                    }
                  ]
              }
          ]
        }
      ]
    }
  ]
    };
}
```

## Configurar a rotina

Faça com que o script seja executado a cada X tempo.




## Sobre

Este tutorial foi escrito com base nos artigos abaixo:
- [RSS Notifications in Google Chat Rooms via AppScript & Google Sheets](https://techupover.medium.com/rss-notifications-in-google-chat-rooms-via-appscript-google-sheets-1f036e8b3279);
- [Código original - Github](https://github.com/usaussie/appscript-chat-rss/blob/master/code.gs);

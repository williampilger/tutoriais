# Instalando o Google Cloud CLI

Independente do sistema operacional, você precisará instalar o CLI para interagir com o GCP via terminal.
Você pode encontrar o passo a passo adequado para seu caso na [página oficial do google](https://cloud.google.com/sdk/docs/install?hl=pt-br);

*Para instalar no Windows*
```p1
(New-Object Net.WebClient).DownloadFile("https://dl.google.com/dl/cloudsdk/channels/rapid/GoogleCloudSDKInstaller.exe", "$env:Temp\GoogleCloudSDKInstaller.exe")
& $env:Temp\GoogleCloudSDKInstaller.exe
```

*Para Ubuntu/Debian*
```sh
sudo apt update
sudo apt install apt-transport-https ca-certificates gnupg curl
sudo curl https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo gpg --dearmor -o /usr/share/keyrings/cloud.google.gpg
echo "deb [signed-by=/usr/share/keyrings/cloud.google.gpg] https://packages.cloud.google.com/apt cloud-sdk main" | sudo tee -a /etc/apt/sources.list.d/google-cloud-sdk.list
sudo apt update && sudo apt install google-cloud-cli
```

Inicie o Google Cloud CLI:
> gcloud init



## Configurando o Google CLI e fazendo login

Você pode verificar a autenticação da sua conta com:
> gcloud auth list

E/ou fazer login em uma nova conta com:
> gcloud auth login

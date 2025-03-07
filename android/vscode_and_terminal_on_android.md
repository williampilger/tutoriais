# Instalando o Visual Studio Code e o Terminal no Android

Neste passo a passo, irei descrever a instalação de uma IDE da minha preferência (VScode) e um terminal *Linux* para execução das aplicações diretamente no Tablet.

Usaremos:
    - [VScode Online](https://vscode.dev) - Que funciona Offline após a instalação;
    - [termux](https://play.google.com/store/apps/details?id=com.termux) - App da Play Store

---


## A instalação

- **Termux**
    - O Termux é facilmente instalado, basta clica no link, e em ˋinstalarˋ.


- **vscode**
    - Acesse o app pelo navegador (pode ser clicando no link);
    - Ele **provavelmente** vai oferecer a instalação, então basta concordar;
    - Se não oferecer, clique nos três pontinhos para acessar as opções da página, e depois em ˋInstalar Appˋ;

---



## A primeira utilização

Para usuários de linux, tudo é intuitivo, então siga seus instintos.

Se você é novo no ramo, veja que será necessário instalar e configurar algumas coisas.

- **Abra o Termux**
    - Passe a tela de boas-vindas... faça o que quiser
    - Atualize o índice de pacotes, rodando o comando abaixo:
        - ˋˋˋ
          apt update
          ˋˋˋ
    - Instale o python (caso seja isso que deseja usar):
        - ˋˋˋ
          apt install python3
          ˋˋˋ
    - Você pode instalar editores de texto ou outras coisas, como o ˋnanoˋ e mais... Mas isso é opcional.
- **Abra o VScode**
    - Pule a tela de boas-vindas... faça o que quiser.
    - Clique em ˋAbrir uma pastaˋ
    - No explorador de arquivos, selecione a **pasta do Termux**, ou uma dentro do diretório dele. O termux não pode acessar arquivos de fora da sua pasta.
        - Se você abrir os três risquinhos à esquerda, provavelmente verá o Termux na lista. Você pode selecionar a pasta inteira, ou criar subpastas... isso é com você. *Se por acaso, você tiver pouca ou nenhuma experiência com Linux, talvez seja mais fácil selecionar a pasta como um todo.*
    - Agora, você já poderá criar um novo arquivo e editar seu conteúdo.
- Criando um exemplo e executando
    - Crie um arquivo ˋexemplo.pyˋ e adicione ˋprint('OOI, TO AQUI')ˋ em seu internior. Salve o arquivo.
    - Volte ao Termux, e digite ˋpython3 exemplo.pyˋ para rodar o seu script.
        - No linux, você usa ˋpython3ˋ ao invez de ˋpythonˋ como comando.

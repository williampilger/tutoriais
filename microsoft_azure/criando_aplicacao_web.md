# Publicando uma aplicação WEB no Azure

Neste passo a passo será publicado um exemplo de site, também de autoria da Alura.

Itens necessários:
- Visual Studio;
- Conta, servidor e banco de dados SQL do Azure;
- Codigo fonte do site. Diponível [AQUI](https://github.com/williampilger/tutoriais/raw/master/microsoft_azure/CodigoFonte.rar).

Na sequência também será criada uma máquina virtual para executrar tarefas na núvem.

## Compilando aplicação WEB exemplo

Abra o projeto exemplo no visual studio. e Adicione seu banco SLQ ao projeto, fazendo:
- Abra o Explorador SLQ: **Exibir** -> **SQL Server Object Explorer**;
- Clique em **Add SQL Server** (representado por um pequeno botão com símbolo de `+`;
- Use as credencias do servidor como administrador;
- Abra as propriedades do banco, clicando com o direito sobre ele e em **Propriedades**;
- Procure pela **Connection String** e copie ela;
- Abra o arquivo **appsettings.json** no projeto da aplicação exemplo, e substitua a **ConnectionString** pela sua;
- **ATENÇAO!!** Substitua as credencias de administrador pelas do **Usuário que criamos para a aplicação**. Importante não usar as credencias de administrador na connection string dentro do app.
- Navegue até: **Ferramentas** -> **Gerenciador de pacotes NuGet** -> **Console do gerenciador de pacotes** e digite o seguinte comando: `dotnet ef database update --project .\CasaDoCodigo.EF --startup-project .\CasaDoCodigoWeb` 
- Compile e execute a solução. A Aplicação agora estará rodando **localmente**, e acessando o banco de dados na nuvem. Caso o banco de dados esteja em branco, ele será preenchido com os livros "padrões".


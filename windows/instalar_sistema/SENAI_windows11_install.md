# Instalando o Windows 11 nos computadores do SENAI

Este guia tem como objetivo detalhar o procedimento para instalação do Windows 11 nos computadores do SENAI.
O processo inclui o download da ISO, criação de mídia bootável, instalação padrão, e execução do post-install; e pode ser realizado por qualquer pessoa com conhecimentos básicos de informática.




## 1️⃣ Download da ISO do sistema (não necessário se seguir a `Opção 1` da próxima seção)

Primeiramente, precisamos da ISO do Windows 11.

- 1. Acesse o site oficial da Microsoft: [Download do Windows 11](https://www.microsoft.com/pt-br/software-download/windows11);
- 2. Localize a seção **Baixar a imagem de disco do Windows 11 (ISO) para dispositivos x64**;
- 3. Selecione `Windows 11 (multi-edition ISO for x64 devices)` e clique em **Baixar agora**;
- 4. Selecione o idioma `Portuguese (Brazil)` e clique em **Confirmar**;
- 5. Clique em **Download de 64 bits** e aguarde o término (a ISO possui aproximadamente `6,2 GB`).


## 2️⃣ Gravando a imagem do sistema em um pendrive

Você pode fazer isso, basicamente, de três formas:

#### Opção 1: Utilizando o Media Creation Tool da Microsoft

O Media Creation Tool é a ferramenta oficial da Microsoft para criar mídias de instalação do Windows, e é a opção mais simples, pois baixa a ISO e cria o pendrive automaticamente.

- 1. Acesse o site oficial da Microsoft: [Download do Windows 11](https://www.microsoft.com/pt-br/software-download/windows11);
- 2. Na seção **Criar mídia de instalação do Windows 11**, clique em **Baixar agora**;
- 3. Execute o Media Creation Tool (não precisa instalar);
- 4. Aceite os termos de licença;
- 5. Selecione a opção **Criar mídia de instalação (unidade flash USB, DVD ou arquivo ISO) para outro computador** e clique em **Avançar**;

#### Opção 2: Utilizando o Rufus

O Rufus é a ferramenta mais indicada para criar pendrives bootáveis com Windows, pois aplica automaticamente as configurações corretas de particionamento (GPT/MBR) e bypass de requisitos.

- 1. Baixe o Rufus em [rufus.ie](https://rufus.ie/pt_BR/);
- 2. Execute o Rufus (não precisa instalar);
- 3. Em **Dispositivo**, selecione o pendrive (mínimo `8 GB`);
- 4. Em **Seleção de boot**, clique em **SELECIONAR** e escolha a ISO do Windows 11;
- 5. Deixe o esquema de partição como `GPT` e o sistema de destino como `UEFI (não CSM)`;
- 6. Clique em **INICIAR**;
- 7. Na janela de opções, marque `Remover requisito de TPM 2.0 e Secure Boot` (caso necessário) e clique em **OK**;
- 8. Confirme a formatação do pendrive clicando em **OK** e aguarde o término.

#### Opção 3: Usando o Ventoy

Se você já tem um pendrive com o Ventoy, siga [este guia](../../flash_usb_ventoy.md) para referência.

Tendo ele em mãos, basta copiar a ISO do Windows 11 para o pendrive, e ele já estará pronto para ser utilizado.



---



## 3️⃣ Instalação do sistema

1. Insira a mídia de instalação (pendrive) no computador onde deseja instalar o Windows 11;
2. Inicie o computador dando boot pelo pendrive;
   1. Normalmente, pressione `F12`, `F8`, ou `Del` na inicialização para acessar o menu de boot (varia por fabricante);
3. Na tela inicial do instalador, selecione:
   - Idioma: `Português (Brasil)`;
   - Formato de hora e moeda: `Português (Brasil)`;
   - Teclado: `Português (Brasil ABNT2)`;
   - Clique em **Avançar** e depois em **Instalar agora**;
4. Na tela de chave de produto, clique em **Não tenho uma chave de produto** (a ativação será automática - As licenças do Senai são OEM);
5. Selecione a edição **Windows 11 Pro** e clique em **Avançar**;
6. Aceite os termos de licença e clique em **Avançar**;
7. Selecione **Personalizada: instalar somente o Windows (avançado)**;
8. Selecione o disco onde o Windows será instalado:
   1. Se houver partições antigas, selecione-as e clique em **Excluir** até restar apenas o "Espaço não alocado";
   2. Selecione o espaço não alocado e clique em **Avançar**;
9. Aguarde o término da instalação — o computador será reiniciado automaticamente algumas vezes.


## 4️⃣ Configuração inicial (OOBE)

Após a instalação, o Windows iniciará o assistente de configuração inicial (OOBE):

1. **Ignorar a obrigatoriedade de conta Microsoft** (para criar conta local):
   1. Quando chegar na tela de conexão à internet, pressione `Shift + F10` para abrir o Prompt de Comando;
   2. Digite o comando abaixo e pressione Enter:
      ```cmd
      oobe\bypassnro
      ```
   3. O computador reiniciará e voltará ao início do assistente — desta vez, selecione **Não tenho internet** e depois **Continuar com configuração limitada**;
2. Preencha os dados de usuário:
   - Nome: `Admin`;
   - Senha: **Preencher a senha default do administrador**;
   - Perguntas de segurança: preencha com qualquer valor padrão;
3. Nas telas seguintes, **desative todas as opções de privacidade** e clique em **Aceitar**;
4. Aguarde o Windows finalizar a configuração da área de trabalho.


## 5️⃣ Renomear o computador

Cada computador deve ter um nome único na rede do SENAI (ex.: `MICRO-001`):

1. Abra as **Configurações** → **Sistema** → **Sobre**;
2. Clique em **Renomear este PC**;
3. Digite o nome do computador (ex.: `MICRO-001`) e clique em **Avançar**;
4. Clique em **Reiniciar agora**.


## 6️⃣ Configuração pós-instalação (script)

Agora, com o sistema instalado e ligado, acesse o usuário `Administrador` que você criou.

1. Abra o navegador (Microsoft Edge) e acesse o repositório com o script [github.com/williampilger/williampilger];
2. Procure pelo post-install do SENAI para Windows;
3. No topo do script, você verá um comando para rodar o script diretamente, sem baixar:
   - O comando exato é:
     ```powershell
     irm https://raw.githubusercontent.com/williampilger/williampilger/main/PostInstallScripts_Windows/ACI_SENAI_BasicWorkstation_Windows11.ps1 | iex
     ```
   - Copie esse comando;
4. Abra o **PowerShell como Administrador**:
   - Clique com o direito no menu Iniciar → **Terminal (Admin)** ou **Windows PowerShell (Admin)**;
5. Cole o comando (`Ctrl+V`) e pressione Enter para executar o script;
6. Aguarde o término da execução e reinicie o computador (respondendo `S` ao final do script, ou manualmente) para aplicar as mudanças.




---

## Sobre

Este guia foi elaborado por [William Pilger](https://github.com/williampilger);

**03 de Junho de 2026** | Bom Princípio - RS

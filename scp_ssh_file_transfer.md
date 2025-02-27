# SCP -> Comando para transferência de arquivos via SSH

Existem diversas formas de transferir arquivos via SSH (Secure Shell), um protocolo que permite a comunicação segura entre dois computadores. As formas mais comuns são:

---

## `scp` (Secure Copy)

O `scp` é um comando baseado em SSH que permite copiar arquivos e diretórios entre um computador local e um remoto, ou entre dois computadores remotos.

**Vantagens:** Simples e fácil de usar para transferências rápidas.

**Desvantagens:** Não possui interface gráfica e pode ser menos conveniente para transferências complexas.

**Sintaxe básica:**
 * Copiar um arquivo local para um servidor remoto:
     ```bash
     scp arquivo_local usuario@servidor_remoto:/caminho/destino
     ```
 * Copiar um arquivo de um servidor remoto para o computador local:
     ```bash
     scp usuario@servidor_remoto:/caminho/arquivo_remoto arquivo_local
     ```
 * Copiar um diretório inteiro:
     ```bash
     scp -r diretorio_local usuario@servidor_remoto:/caminho/destino
     ```

---

## `sftp` (SSH File Transfer Protocol)

O `sftp` é um protocolo interativo que permite navegar, transferir e gerenciar arquivos em um servidor remoto através de uma interface de linha de comando semelhante ao FTP.

**Vantagens:** Permite navegar e gerenciar arquivos remotamente de forma interativa.

**Desvantagens:** Interface de linha de comando pode ser menos intuitiva para alguns usuários.

**Sintaxe básica:**
* Conectar a um servidor remoto:
   ```bash
   sftp usuario@servidor_remoto
   ```
* comandos internos no sftp:
   * `put arquivo_local`: Envia um arquivo para o servidor remoto.
   * `get arquivo_remoto`: Baixa um arquivo do servidor remoto.
   * `ls`: Lista os arquivos no diretório remoto.
   * `cd`: Altera o diretório remoto.

---

### Recomendações

* Para transferências rápidas de arquivos únicos ou pequenos diretórios, o `scp` é uma ótima opção.
* Para gerenciar arquivos remotamente de forma interativa, o `sftp` é mais adequado.
* Para usuários que preferem uma interface gráfica, o FileZilla, WinSCP ou Cyberduck são excelentes alternativas.

### Ferramentas gráficas

* **FileZilla:** Um cliente FTP/SFTP gratuito e de código aberto com uma interface gráfica intuitiva.
* **WinSCP:** Um cliente SFTP e SCP gratuito e de código aberto para Windows.
* **Cyberduck:** Um cliente FTP, SFTP, WebDAV, Amazon S3, Azure e Google Cloud Storage gratuito e de código aberto para macOS e Windows.
* **Vantagens:** Interface gráfica facilita a transferência e o gerenciamento de arquivos.
* **Desvantagens:** Podem exigir instalação de software adicional.

---


# Sobre

*Agradecimento ao Google Gemini Pro* por escrever **quase** todo este passo a passo.

* [Documentação do `scp`](https://www.geeksforgeeks.org/scp-command-in-linux-with-examples/)
* [ocumentação do `sftp`](https://docs.couchdrop.io/walkthroughs/using-sftp-clients/openssh-sftp)


**By: William Pilger | github.com/williampilger**

2025/02/27 11:03 | Bom Princípio - RS

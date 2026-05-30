# Instalação de app Java (.jar) no Linux e criação de atalho no menu de apps

Neste tutorial usei como exemplo o `Astah UML`, na versão JAVA.
Meu sistema no momento é o `Xubuntu 24.04 LTS`.

## Pré-requisitos

- Java instalado (versão 11 ou superior)
- Pasta do software já baixado e extraído

Verifique se o Java está disponível:

```bash
java -version
```

---

## 1. Mover o Astah para uma pasta do sistema

O recomendado é mover a pasta do Astah para `/opt/`, que é o diretório padrão do Linux para aplicativos de terceiros instalados manualmente.

Supondo que a pasta extraída se chama `astah_uml` e está na sua pasta de Downloads:

```bash
sudo mv ~/Downloads/astah_uml /opt/astah_uml
```

Em seguida, dê permissão de execução ao script principal:

```bash
sudo chmod +x /opt/astah_uml/astah-uml.jar
```

> **Observação:** o nome exato da pasta e do executável pode variar conforme a versão baixada. Ajuste os comandos se necessário. Para confirmar o nome do executável, rode `ls /opt/astah_uml/` após mover a pasta.

---

## 2. Criar o atalho no menu de aplicativos

O menu de aplicativos no Linux (GNOME, KDE, XFCE etc.) lê arquivos `.desktop` localizados em `~/.local/share/applications/`. Criar um arquivo ali é suficiente para o Astah aparecer no menu.

### Opção A — Passo a passo com o nano

Abra o editor de texto no terminal:

```bash
nano ~/.local/share/applications/astah-uml.desktop
```

Cole o conteúdo abaixo dentro do editor:

```ini
[Desktop Entry]
Version=1.0
Type=Application
Name=Astah UML
Comment=Ferramenta de modelagem UML
Exec=java -jar /opt/astah_uml/astah-uml.jar
Icon=/opt/astah_uml/astah.ico
Terminal=false
Categories=Development;IDE;
StartupNotify=true
```

Salve e saia: pressione `Ctrl+O`, confirme com `Enter`, depois `Ctrl+X`.

Por fim, dê permissão de execução ao arquivo:

```bash
chmod +x ~/.local/share/applications/astah-uml.desktop
```

---

### Opção B — Comando único para colar e rodar de uma vez

O bloco abaixo faz tudo automaticamente: cria o arquivo `.desktop` com o conteúdo correto e aplica a permissão de execução.

```bash
cat > ~/.local/share/applications/astah-uml.desktop << 'EOF'
[Desktop Entry]
Version=1.0
Type=Application
Name=Astah UML
Comment=Ferramenta de modelagem UML
Exec=java .jar /opt/astah_uml/astah-uml.jar
Icon=/opt/astah_uml/astah.ico
Terminal=false
Categories=Development;IDE;
StartupNotify=true
EOF
chmod +x ~/.local/share/applications/astah-uml.desktop
```

Cole o bloco inteiro no terminal e pressione `Enter`.

---

## 3. Atualizar o banco de aplicativos (opcional)

Em alguns ambientes de desktop o atalho aparece imediatamente; em outros pode ser necessário forçar a atualização:

```bash
update-desktop-database ~/.local/share/applications/
```

Após isso, o Astah UML deverá aparecer no menu de aplicativos do seu sistema.

---

## Resolução de problemas comuns

| Situação | Solução |
|---|---|
| Ícone não aparece | Verifique se o caminho do ícone está correto com `ls /opt/astah_uml/icon/` |
| App não abre pelo menu | Teste direto no terminal: `java -jar /opt/astah_uml/astah-uml.jar` e veja o erro |
| Executável não encontrado | Confirme o nome exato com `ls /opt/astah_uml/` e ajuste o campo `Exec=` |
| Java não encontrado | Instale com `sudo apt install default-jre` (Debian/Ubuntu) |

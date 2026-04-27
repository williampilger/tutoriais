# Instalando o Docker no Ubuntu

> ⚠️ Importante: Existem duas formas de instalar o Docker no Ubuntu, e a diferença é relevante.

A instalação do `docker.io` (Método 1, versão da Canonical) é muito mais simples, no entanto, ela usa uma versão fixada pela canonical,
e atualizações e correções levam consideravelmente mais tempo para chegarem a este pacote.
É recomendado o uso do **Método 2** se você quer garantia de atualizações da própria desenvolvedora.

---

## Método 1: Instalação do `docker.io` - Release da Canonical

```bash
sudo apt update

# Docker engine
sudo apt install docker.io -y

# Docker docker-compose
sudo apt install docker-compose

# Autorização do usuário do docker (pra não ter que rodar tudo com sudo)
sudo usermod -aG docker $USER
newgrp docker #aplica as alterações imediatamente
```

---

## Método 2: Instalação do `docker-ce` - Release oficial

Passo a passo extraído da [documentação oficial](https://docs.docker.com/engine/install/ubuntu/).

Eu estou usando o `Ubuntu Server 24.04 LTS` neste exemplo.

**Adicionando os Repositórios no APT**
```bash
# Add Docker's official GPG key:
sudo apt update
sudo apt install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources:
sudo tee /etc/apt/sources.list.d/docker.sources <<EOF
Types: deb
URIs: https://download.docker.com/linux/ubuntu
Suites: $(. /etc/os-release && echo "${UBUNTU_CODENAME:-$VERSION_CODENAME}")
Components: stable
Architectures: $(dpkg --print-architecture)
Signed-By: /etc/apt/keyrings/docker.asc
EOF

sudo apt update
```

**Instalando**
```bash
sudo apt install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

# Autorização do usuário do docker (pra não ter que rodar tudo com sudo)
sudo usermod -aG docker $USER
newgrp docker #aplica as alterações imediatamente
```


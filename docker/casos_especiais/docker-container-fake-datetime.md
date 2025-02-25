# Container Docker com Data/Hora diferentes do Host

Existem algumas formas de fazer isso.

*Agradecimento do ChatGPT que escreveu **quase** todo este tutorial.*

---

### 1. **Usando a variável de ambiente `TZ` (Fuso Horário)**
Se o objetivo for apenas mudar o fuso horário, você pode especificar uma timezone diferente ao criar o container:

```bash
docker run -it --rm -e TZ=America/New_York ubuntu date
```

Isso muda apenas o fuso horário, mas a hora continua sincronizada com o sistema.

---

### 2. **Usando `fake-hwclock` para definir um horário manualmente**
Se quiser **definir um horário fixo e independente**, pode usar `fake-hwclock`:

```bash
docker run -it --rm --cap-add=SYS_TIME ubuntu bash
```

Dentro do container, instale e configure:

```bash
apt update && apt install -y fake-hwclock
date --set "2023-01-01 12:00:00"
fake-hwclock save
```

Isso força o container a "lembrar" esse horário mesmo após restart.

---

### 3. **Desvinculando o relógio do host (`timedatectl set-ntp off`)**
Se precisar de algo mais preciso, pode desligar a sincronização de tempo no container:

```bash
docker run -it --rm --cap-add=SYS_TIME ubuntu bash
timedatectl set-ntp off
date -s "2022-12-31 23:59:59"
```

O `--cap-add=SYS_TIME` permite alterar a hora dentro do container.

---

### 4. **Criando um container sem `/etc/localtime` vinculado**
Normalmente, o Docker compartilha o `/etc/localtime` com o host. Para evitar isso:

```bash
docker run -it --rm -v /dev/null:/etc/localtime:ro ubuntu bash
```

Isso impede que o container herde a configuração de horário da máquina host.

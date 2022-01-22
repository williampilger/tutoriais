# Speedteste via Linha de comando (Linux)

Neste exemplo, estou usando as versões "não instaladas" do speedtest. Para ver todas as possibilidades acesse [a página de insttruções completa do sppedtest.net](https://www.speedtest.net/pt/apps/cli).


## Fazendo o download do cliente

Existem alguns disponíveis.

- **i386** : `https://install.speedtest.net/app/cli/ookla-speedtest-1.1.1-linux-i386.tgz`
- **x86_64** : `https://install.speedtest.net/app/cli/ookla-speedtest-1.1.1-linux-x86_64.tgz`
- **armel** : `https://install.speedtest.net/app/cli/ookla-speedtest-1.1.1-linux-armel.tgz`
- **armhf** : `https://install.speedtest.net/app/cli/ookla-speedtest-1.1.1-linux-armhf.tgz`
- **aarch64** : `https://install.speedtest.net/app/cli/ookla-speedtest-1.1.1-linux-aarch64.tgz`

Observe que no link é informada a versão, com o passar do tempo este tutorial pode ficar desatualizado, e vale a pena conferir os links atualizados no link acima.

Escolha o adequado para a sua distribuição, e siga para o proximo passo.

### Use o curl para fazer o download via linha de comando

> curl https://install.speedtest.net/app/cli/ookla-speedtest-1.1.1-linux-armhf.tgz > speedtest.tgz

No exemplo acima, estou baixando a versão adequada para minha raspberrypi, rodando o ubuntu server.

## Extrair os arquivos

> tar -xzvf speedtest.tgz

## Executar o teste

./speedtest

## EXTRA - Meu script completo

```sh
mkdir Downloads/SpeedTest
cd Downloads/SpeedTest
curl https://install.speedtest.net/app/cli/ookla-speedtest-1.1.1-linux-armhf.tgz > speedtest.tgz
tar -xzvf speedtest.tgz
rm speedtest.tgz
./speedtest
```

Ps.: Na primeira execução será necessário concordar com os termos de uso, digitando `yes` três vezes.


## Sobre

By: will.i.am | github.com/williampilger

2022.01.22 | Harmonia - RS - Brasil

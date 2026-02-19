# Inspecionar o Armazenamento do Ubuntu

*Este é um tutorial preguiçoso... Nenhuma solução muito técnica nem de terminal te aguarda...*

Eu, gosto de inspecionar o espaço com o *Analizador de Espaço* do próprio Gnome. **Mas ele tem uma limitação bem chata** não te alertando sobre o espaço que não analizou do disco.

Então, muitas vezes não mostra tudo (como os lixos do Docker, que são esmagadores se você trabalha com Docker constantemente. Eu já tive mais de 120GB esquecidos só em cache e imagens inúteis do Docker Engine).

Então, rode o *Analizador de Espaço* como super-admin:

```bash
sudo baobab /
```

Ps.: Você pode trocar `/` pelo diretório que você quer analizar graficamente.

Ps.2: Você não precisa rodar sempre como `sudo`, se não estiver analizano espaço protegido do sistema.

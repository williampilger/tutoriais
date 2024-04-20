# Trabalhando com Ambientes Virtuais em Python

Os ambientes virtuais são úteis para você instalar as bibliotecas necessárias, e depois poder descartar todo o ambiente sem interferir na máquina hospedeira.


## Criando o Ambiente virtuai

*Microsoft Windows*
```bat
python -m venv nome_do_ambiente
```

*Linux - Ubuntu-based*
```sh
sudo apt install python3-venv
python3 -m venv nome_do_ambiente
```

## Ativando o ambiente

*Microsoft Windows*
```bat
nome_do_ambiente\Scripts\activate
```

*Linux - Ubuntu-based*
```sh
source nome_do_ambiente/bin/activate
```

## Desativando o ambiente

```sh
deactivate
```

Para excluir o ambiente, basta remover a pasta do nome do ambiente.

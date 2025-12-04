# Como fazer o download de múltiplos arquivos de um bucket do Google Cloud Storage?

Isso é útil para downloads "normais" de buckets, ou para baixar exportações grandes de backups que usam buckets (como a exportação do Google Workspace de uma organização inteira).

Em casos de downloads de backups, o Consolde do Google Workspace vai lhe fornecer algo como:

```
gsutil -m cp \
  "gs://takeout-export-t5921456-fb87-400a-tg66-93632b44743e/20251202T121059Z/sample@sample.com.br/takeout-20251202T121101Z-001.zip" \
  "gs://takeout-export-t5921456-fb87-400a-tg66-93632b44743e/20251202T121059Z/sample@sample.com.br/takeout-20251202T121101Z-5-001.zip" \
  "gs://takeout-export-t5921456-fb87-400a-tg66-93632b44743e/20251202T121059Z/sample@sample.com.br/takeout-20251202T121101Z-7-001.zip" \
  "gs://takeout-export-t5921456-fb87-400a-tg66-93632b44743e/20251202T121059Z/sample@sample.com.br/takeout-20251202T121101Z-7-002.zip" \
  "gs://takeout-export-t5921456-fb87-400a-tg66-93632b44743e/20251202T121059Z/sample@sample.com.br/takeout-20251202T121101Z-7-003.zip" \
  "gs://takeout-export-t5921456-fb87-400a-tg66-93632b44743e/20251202T121059Z/sample@sample.com.br/takeout-20251202T121101Z-9-001.zip" \
  "gs://takeout-export-t5921456-fb87-400a-tg66-93632b44743e/20251202T121059Z/sample@sample.com.br/takeout-20251202T121101Z-9-002.zip" \
  .
```

Se você estiver querendo fazer o download manualmente, deverá montar algo parecido com o que vê acima.

## O que preciso para prosseguir?

Obviamente, ter o `gcloud` - que vem na **CLI do Google Cloud** - instalado no computador. Caso não tenha, instale seguindo [este tutorial](../GoogleCloudPlatform/install_cli.md) (ou outro método confiável que você tenha).

Esteja logado na sua conta (com acesso ao backup/bucket):
> gcloud auth login


## Fazer o download

### Usando Linux
Basta colar o código fornecido no terminal.


### No Windows
O processo é levemente mais difícil.

Você precisará alterar o marcado de quebra de linha, pois o windows usa ``` e não `\` para isso.

E, na hora de executar o PowerShell, será necessário executá-lo como Administrador. Se não, terás problema de acesso ao `gsutil`.

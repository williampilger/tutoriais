# Rclone - Montar e sincronizar unidades remotas (online) no linux

Para configurar uma nova unidade use:

> rclone config

Então, informe um nome para a unidade, e o restante dos dados podes ir deixando em branco e seguindo o passo-a-passo.

Depois de confiugrado o remote, você pode montar ele usando, por exemplo:

> rclone mount $REMOTE_NAME: ~/path/to/existent/empty/folder --daemon

---

### Ou, caso queira maios agilidade para listagem dos diretórios:

```bash
# Montando a pasta ativando cache
rclone mount $REMOTE_NAME: ~/path/to/existent/empty/folder \
  --vfs-cache-mode full \
  --vfs-cache-max-size 10G \
  --vfs-cache-max-age 1h \
  --dir-cache-time 12h \
  --poll-interval 15s \
  --daemon
# Pré carregando a árvore de diretório (opcional)
rclone tree $REMOTE_NAME:path --max-depth=5
```

#### Parâmetros explicados:

* `--vfs-cache-mode full`: ativa o cache completo (ideal para leitura e escrita).
* `--vfs-cache-max-size`: tamanho máximo do cache no disco.
* `--vfs-cache-max-age`: tempo máximo que os arquivos ficam no cache.
* `--dir-cache-time`: quanto tempo manter a árvore de diretórios em cache.
* `--poll-interval`: verifica alterações remotamente (melhora sincronia).
* `--allow-other`: permite acesso por outros usuários (use com cuidado e com `fusermount` instalado).


---


## Google Drive - Observações

Durante o `rclone config`, marque `NÃO` para a configuração de drives compartilhados se você estiver tentando montar `meu drive`.
Caso queira montar uma unidade compartilhada, então responda `sim`.

Os drives compartilhados precisação ser montados um a um.


---


## Outros Comandos

| Comando | Descrição |
| --- | --- |
| `rclone listremotes` | Listar remotes |
| `rclone config` | Serve para manipular tudo, embora já tenha sudo citado acima, escrevendo aqui novamente para reforçar: você pode listar, adicionar e remover remotes. |
| `rclone config delete $REMOTE_NAME` | Excluir um remote |

# Rclone - Montar e sincronizar unidades remotas (online) no linux

Para configurar uma nova unidade use:

> rclone config

Então, informe um nome para a unidade, e o restante dos dados podes ir deixando em branco e seguindo o passo-a-passo.

Depois de confiugrado o remote, você pode montar ele usando, por exemplo:

> rclone mount $REMOTE_NAME: ~/path/to/existent/empty/folder --daemon


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

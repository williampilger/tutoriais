# Comandos do Terraform

Aqui, estou listando uns comandos que **EU** acho diferenciados e importantes **PRA MIM**!



#### `terraform untaint <resource_address>`

Comando exemplo:
> terraform untaint 'module.cloudrun_service.google_cloud_run_v2_service.services["app-budgeting-23002"]'

Isso marca o recurso como "não-tentado", como se o terraform nunca tivesse tentado criar ele (ou aplicar as alterações) no GCP.
Isso pode ser útil para não precisar destruir e re-criar um item.



#### `terraform force-unlock <lock-id>`

O uso do comando pode ser perigoso.

**O que é o lock-file?** Quando um usuário ou processo inicia uma modificação no estado do Terraform, o arquivo fica em lock, para impedir modificação simultânea e perda de dados.

Se você tiver CERTEZA de que nem você (em outro processo) nem nenhuma outra pessoa esteja modificando o estado, você pode rodar este comando sem medo.

Considere esperar um pouco para tentar novamente, pode ser mais seguro.

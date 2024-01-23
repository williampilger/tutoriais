# Configuração e verificação de configuração SPF em domínios

## Conferir a configuração SPF de um site

Se você estiver usando `Linux` ou `MAC`
> dig +short TXT yourdomain.com

Ou `Windows`
> nslookup -type=TXT yourdomain.com

Um resultado como `v=spf1 include:_spf.locaweb.com.br ?all` indica que e-mails vindos de `locaweb.com.br` são válidos e o final indica:

| Code | Significado |
| --- | --- |
| `?all` | `soft-fail` - Emails que reprovam podem ser entregues normalmente |
| `~all` | `soft-fail` - Emails podem ser marcados como Span |
| `-all` | `hard-fail` - Emails não devem ser entregues |



# Docker Prune: inspecionar uso de disco e fazer limpeza com segurança

```
⚠️ Tutorial gerado por IA em sua esmagadora maioria!
```

Este guia é para quem já usa Docker há tempo e quer **ver exatamente onde está o consumo de espaço** e **limpar sem dor**.

> Dica rápida: prefira inspeção → limpeza pontual → limpeza agressiva. Evite rodar `prune` no impulso.

---

## 1) Visão geral do uso de espaço

| Objetivo | Comando | Observações |
|---|---|---|
| Resumo geral do consumo (imagens, containers, volumes, cache) | `docker system df` | Melhor primeiro passo |
| Resumo detalhado (por item) | `docker system df -v` | Mostra onde está “gordo” |
| Quanto o Docker ocupa no disco (Linux) | `sudo du -sh /var/lib/docker` | Para visão real do diretório do Docker |
| Top diretórios dentro do Docker (Linux) | `sudo du -h /var/lib/docker | sort -h | tail -n 30` | Útil para caça a vazamentos |

---

## 2) Proteções antes de limpar (não perder coisa importante)

### 2.1 Identifique e marque o que é importante
| O que proteger | Como identificar | Como “proteger” (prática) |
|---|---|---|
| Dados persistentes | Volumes com nome e containers de DB | **Use volumes nomeados** (não “anônimos”) e documente-os |
| Imagens base ou releases | Imagens usadas em produção | **Mantenha pelo menos 1 container apontando para a imagem** ou exporte (`save`) |
| Workspaces locais | Bind mounts (`-v /host:/container`) | Não serão apagados por `prune`, mas cuidado ao remover containers |

### 2.2 Backup rápido (quando vale a pena)
| Caso | Comando | Observações |
|---|---|---|
| Exportar uma imagem para arquivo | `docker save -o minha-imagem.tar repo:tag` | Para guardar antes de limpar imagens |
| Exportar/importar volume (backup simples) | `docker run --rm -v meu_volume:/v -v "$PWD":/b busybox tar -czf /b/meu_volume.tgz -C /v .` | Salva conteúdo do volume em tar.gz |
| Restaurar volume (do backup acima) | `docker run --rm -v meu_volume:/v -v "$PWD":/b busybox tar -xzf /b/meu_volume.tgz -C /v` | Restaura no volume |

> Observação: `prune` só remove **volumes não usados**. Mas “não usado” pode incluir volumes que você queria manter e não estão ligados a nenhum container.

---

## 3) Containers: inspeção e limpeza

| Objetivo | Comando | Observações |
|---|---|---|
| Listar containers rodando | `docker ps` |  |
| Listar todos (inclui parados) | `docker ps -a` |  |
| Ver tamanho por container | `docker ps -a --size` | Bom para achar containers enormes |
| Logs grandes (visão) | `docker logs --tail 200 <container>` | Se logs cresceram demais, considere rotação no daemon |
| Inspecionar um container | `docker inspect <container>` | Montagens, redes, etc |
| Parar todos os containers | `docker stop $(docker ps -q)` | Use com cuidado |
| Remover um container | `docker rm <container>` | Para parado |
| Remover forçando (mata e remove) | `docker rm -f <container>` |  |
| Remover todos os containers parados | `docker container prune` | Remove apenas parados |
| Remover todos os containers (parados e rodando) | `docker rm -f $(docker ps -aq)` | Nuclear: você derruba tudo |

---

## 4) Imagens: inspeção e limpeza

| Objetivo | Comando | Observações |
|---|---|---|
| Listar imagens | `docker images` |  |
| Listar imagens com digest/metadata | `docker image ls --digests` |  |
| Ver imagens “dangling” | `docker images -f dangling=true` | Tags `<none>` |
| Ver o que está “unused” | `docker system df -v` | Mostra imagens não usadas |
| Remover imagens dangling | `docker image prune` | Conservador |
| Remover imagens não usadas (inclui não-dangling) | `docker image prune -a` | Atenção: remove muita coisa |
| Remover uma imagem específica | `docker rmi <image>` | Pode falhar se algum container usa |
| Remover por padrão “sem perguntar” | `docker image prune -a -f` | Use quando tiver certeza |

**Proteção prática para imagens importantes**
- Se você quer garantir que uma imagem não seja considerada “unused”, mantenha **um container parado** baseado nela (ex.: `docker create --name keep_<x> <image>`).  
  Depois, quando quiser liberar, você remove esse container.

---

## 5) Volumes: inspeção e limpeza (onde mais dá ruim)

| Objetivo | Comando | Observações |
|---|---|---|
| Listar volumes | `docker volume ls` |  |
| Inspecionar volume | `docker volume inspect <volume>` | Mostra mountpoint |
| Ver volumes órfãos (candidatos a limpeza) | `docker volume ls -qf dangling=true` | “dangling” = não anexado |
| Ver quais containers usam volumes | `docker ps -a --format '{{.Names}}'` | Combine com `inspect` se precisar |
| Remover volumes não usados | `docker volume prune` | Conservador, mas pode apagar coisa “esquecida” |
| Remover volume específico | `docker volume rm <volume>` | Só se não estiver em uso |
| Remover TODOS volumes dangling | `docker volume rm $(docker volume ls -qf dangling=true)` | Mais direto que prune |

**Proteção prática para volumes importantes**
- Use **volumes nomeados** (ex.: `meu_db_data`) em vez de volumes anônimos.
- Se você quer “proteger” um volume, **mantenha um container parado** anexado a ele:
  - `docker create --name keep_volume -v meu_volume:/data busybox`
  - Assim o volume deixa de ser “unused” para `prune`.

---

## 6) Redes: inspeção e limpeza

| Objetivo | Comando | Observações |
|---|---|---|
| Listar redes | `docker network ls` |  |
| Inspecionar rede | `docker network inspect <rede>` | Ver containers ligados |
| Remover redes não usadas | `docker network prune` | Remove redes órfãs |
| Remover rede específica | `docker network rm <rede>` | Só se não estiver em uso |

---

## 7) Build cache: inspeção e limpeza (BuildKit)

| Objetivo | Comando | Observações |
|---|---|---|
| Ver uso de cache de build | `docker builder du` | Requer BuildKit |
| Limpar cache não usado (conservador) | `docker builder prune` |  |
| Limpar TODO cache (agressivo) | `docker builder prune -a` | Pode aumentar tempo de builds depois |
| Limpar cache até um limite | `docker builder prune --filter 'until=24h'` | Bom para manutenção periódica |

---

## 8) Limpeza “por níveis” (receitas rápidas)

### Nível 1: seguro (mínimo risco)
| Ação | Comando |
|---|---|
| Remover containers parados | `docker container prune` |
| Remover imagens dangling | `docker image prune` |
| Remover redes órfãs | `docker network prune` |
| Ver quanto sobrou | `docker system df -v` |

### Nível 2: moderado (remove o que não está sendo usado)
| Ação | Comando |
|---|---|
| Remover imagens não usadas | `docker image prune -a` |
| Remover cache de build | `docker builder prune` |
| Verificação | `docker system df -v` |

### Nível 3: agressivo (o “praticamente tudo”)
| Ação | Comando | Atenção |
|---|---|---|
| Limpeza geral (imagens, containers parados, redes, cache) | `docker system prune -a` | Remove imagens não usadas |
| Inclui volumes não usados | `docker system prune -a --volumes` | Pode apagar volumes “esquecidos” |

---

## 9) Descobrir “quem está usando o quê” (troubleshooting rápido)

| Objetivo | Comando | Observações |
|---|---|---|
| Ver mounts e volumes de um container | `docker inspect -f '{{json .Mounts}}' <container> | jq` | Requer `jq` |
| Ver imagem usada por cada container | `docker ps -a --format 'table {{.Names}}\t{{.Image}}\t{{.Status}}'` | Ótimo para mapear dependências |
| Ver redes por container | `docker inspect -f '{{json .NetworkSettings.Networks}}' <container> | jq` |  |
| Identificar volumes “dangling” e decidir | `docker volume ls -qf dangling=true` | Liste e revise antes de remover |

---

## 10) Sugestões para evitar crescimento infinito

| Problema comum | Mitigação |
|---|---|
| Builds acumulando cache | Limpeza periódica: `docker builder prune --filter 'until=168h'` |
| Logs gigantes de containers | Configure log driver com rotação no daemon (`json-file` com `max-size` e `max-file`) |
| Volumes anônimos se acumulando | Preferir volumes nomeados e remover containers com `--rm` quando fizer sentido |
| Muitas imagens antigas de CI | Tagging consistente e limpeza por rotina (prune em ambientes de build) |

---

## Checklist rápido (o que eu faria em 60 segundos)

1. `docker system df -v`  
2. `docker ps -a --size`  
3. `docker volume ls -qf dangling=true` (revisar se tem algo valioso)  
4. Rodar nível 1 (seguro) e reavaliar  
5. Só então considerar nível 2 ou 3


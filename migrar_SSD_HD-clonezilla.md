# Tutorial: Como Trocar o HD ou SSD por outro Igual ou Maior com Migração de Dados

> **💡 Importante:** Tutorial criado para Authenty, e formatado com ajuda do Github Copilot.

Este tutorial vai te ensinar como substituir o SSD/HD do seu PC por outro, mantendo todos os seus dados, programas e sistema operacional intactos.

Temos três opções para realizar a migração
- [Em outro PC - Windows](##)
- [Em outro PC - Com adaptador USB](##)
- [Clonezilla - Mais indicado](##)

------


## 📋 O que você vai precisar

### Hardware
- **SSD novo** (maior capacidade)
- **Cabo SATA** (se for SSD SATA) ou slot M.2 livre (se for M.2)
- **Fonte de alimentação SATA** (para SSD SATA)
- **Adaptador USB para SSD** (opcional, mas recomendado)
- **Chaves de fenda** Phillips

### Software
- **Software de clonagem** (gratuitos):
  - Macrium Reflect Free
  - EaseUS Todo Backup Free
  - AOMEI Backupper Standard
  - Clonezilla (mais avançado, mas é o método recomendado)


## ⚠️ Precauções Importantes

- **Este processo apagará** todos os dados do SSD novo
- **A clonagem pode demorar** várias horas dependendo do tamanho
- **Mantenha o SSD antigo** como backup por alguns dias
- **Desligue completamente o PC** e desconecte da tomada
- Use **pulseira antiestática** ou toque em uma superfície metálica aterrada
- **Anote a posição dos cabos** antes de desconectar, se você não tiver familiaridade com isso


---

## 🔧 Método 1 (EM OUTRO PC): Migração com Ambos os SSDs Conectados

### Passo 1: Preparação
1. **Desligue o PC** completamente
2. **Desconecte da tomada**
3. **Abra o gabinete** (geralmente parafusos traseiros)
4. **Localize o SSD atual**

### Passo 2: Conectar o SSD Novo
1. **Conecte o novo SSD** em um slot livre:
   - **SATA**: Conecte cabo SATA na placa-mãe e alimentação da fonte
   - **M.2**: Instale no slot M.2 livre e fixe com parafuso

2. **Feche o gabinete temporariamente**
3. **Ligue o PC**

### Passo 3: Verificar Reconhecimento
1. **Entre no Windows**
2. **Abra o Gerenciador de Disco**:
   - Pressione `Win + X` → "Gerenciamento de disco"
3. **Verifique se o novo SSD aparece**
4. **Inicialize o disco** se necessário (clique direito → "Inicializar disco")

### Passo 4: Clonar o SSD
1. **Baixe e instale** um software de clonagem (ex: Macrium Reflect Free)
2. **Execute o software**
3. **Selecione "Clone this disk"**
4. **Escolha o SSD origem** (atual)
5. **Escolha o SSD destino** (novo)
6. **Configure as partições**:
   - Marque "Fit partitions to fill destination disk"
7. **Inicie a clonagem** (pode demorar 1-3 horas)

### Passo 5: Trocar os SSDs
1. **Desligue o PC** após a clonagem
2. **Desconecte o SSD antigo**
3. **Conecte o SSD novo na conexão principal**:
   - Use os mesmos cabos do SSD antigo
   - Para M.2: mova para o slot principal se necessário

### Passo 6: Configurar Boot
1. **Ligue o PC**
2. **Entre na BIOS/UEFI** (geralmente F2, F12 ou DEL na inicialização)
3. **Vá em Boot Options**
4. **Defina o novo SSD como primeiro** na ordem de boot
5. **Salve e saia** (F10)


---

## 🔧 Método 2 (EM OUTRO PC): Migração com Adaptador USB

### Quando usar
- Quando não há slots livres no PC
- Para laptops com apenas um slot SSD
- Para maior praticidade

### Passo 1: Conectar via USB
1. **Conecte o SSD novo** no adaptador USB
2. **Conecte no PC**
3. **Aguarde reconhecimento** do Windows

### Passo 2: Clonar
1. **Execute o software de clonagem**
2. **Clone do SSD interno** para o SSD USB
3. **Aguarde conclusão**

### Passo 3: Substituir Fisicamente
1. **Desligue o PC**
2. **Remova o SSD antigo**
3. **Instale o SSD novo** no local do antigo
4. **Feche o gabinete**


---

## 🔧 Método 3: Migração com Clonezilla (Live Boot)

### Quando usar
- Para máxima compatibilidade e controle
- Quando outros softwares falharam
- Para clonagem bit-a-bit mais precisa
- Em situações onde o Windows não inicia

### Preparação Necessária
> **💡 Importante:** Provavelmente o departamento de TI já possui um pendrive com Ventoy/Clonezilla. Consulte antes de criar um novo!

Se precisar criar o pendrive bootável, siga o [tutorial de instalação do Ventoy](flash_usb_ventoy.md) e baixe a ISO do [Clonezilla](https://clonezilla.org/clonezilla-live.php) (mas que também deve estar disponível no repositório de softwares da empresa!).

### Passo 1: Conectar Ambos os SSDs
1. **Conecte o SSD novo** no PC:
   - Via adaptador USB externo, OU
   - Instalado internamente em slot livre
2. **Mantenha o SSD antigo** conectado
3. **Conecte o pendrive** com Clonezilla

### Passo 2: Boot pelo Clonezilla
1. **Reinicie o PC**
2. **Acesse o menu de boot** (F12, F11, F8, ESC)
3. **Selecione** o pendrive
4. **Escolha** Clonezilla Live no menu do Ventoy
5. **Aguarde** o carregamento do sistema

### Passo 3: Configuração Inicial
1. **Selecione idioma**: Choose language → `pt_BR.UTF-8` ou `en_US.UTF-8`
2. **Configurar teclado**: `Don't touch keymap`
3. **Iniciar Clonezilla**: `Start Clonezilla`
4. **Modo de operação**: `device-device` (trabalhar diretamente com discos)
5. **Modo de clonagem**: `Beginner mode` (modo iniciante)

### Passo 4: Seleção dos Discos
1. **Tipo de clonagem**: `disk_to_local_disk` (disco para disco local)
2. **Disco origem**: Selecione o SSD antigo (geralmente menor)
   - Ex: `sda` (240GB) ← SSD atual
3. **Disco destino**: Selecione o SSD novo (geralmente maior)
   - Ex: `sdb` (500GB) ← SSD novo
4. **⚠️ ATENÇÃO**: Verifique cuidadosamente - dados do destino serão apagados!

### Passo 5: Opções de Clonagem
1. **Verificação**: `-sfsck` (pular verificação do sistema de arquivos - mais rápido)
2. **Modo de clonagem**: `-pa choose` (escolher o que fazer após clonagem)
3. **Redimensionamento**: `-k1` (usar todo o espaço do disco de destino)
4. **Confirmação**: Digite `y` quando solicitado

### Passo 6: Processo de Clonagem
1. **Confirme novamente** digitando `y`
2. **Digite o nome do disco** destino para confirmação final
3. **Aguarde** a clonagem (pode demorar 1-4 horas)
4. **Progresso** será mostrado em tempo real

### Passo 7: Finalização
1. **Após conclusão**: Selecione `poweroff` para desligar
2. **Remova o pendrive**
3. **Desconecte o SSD antigo**
4. **Configure o SSD novo** como disco principal

### Passo 8: Expandir Partição (Se Necessário)
1. **Inicie pelo SSD novo**
2. **Abra Gerenciador de Disco** no Windows
3. **Estenda a partição** para usar todo o espaço disponível

### Comandos Úteis no Clonezilla

#### Para usuários avançados:
```bash
# Clonar com compressão (mais lento, mas economiza espaço)
-z1p

# Verificar integridade após clonagem
-scs

# Clonar apenas setores utilizados
-q2

# Exemplo de comando completo:
ocs-sr -q2 -c -j2 -z1p -i 4096 -sfsck -scs -k1 -p choose savedisk save_name sda
```


---

## 🔍 Verificações Pós-Migração

### Teste Inicial
1. **Ligue o PC**
2. **Verifique se o Windows inicia** normalmente
3. **Confirme se todos os programas** funcionam
4. **Teste os arquivos pessoais**

### Verificar Espaço
1. **Abra "Este Computador"**
2. **Verifique o espaço total** do disco
3. **Se necessário, estenda a partição**:
   - Gerenciador de Disco → Clique direito na partição → "Estender volume"

### Performance
1. **Execute verificação de disco**:
   ```
   chkdsk C: /f
   ```
2. **Otimize o SSD**:
   - Configurações → Sistema → Armazenamento → Otimizar unidades



---

## 🛠️ Solução de Problemas Comuns

### PC não liga após a troca
- **Verifique conexões** SATA/M.2
- **Confirme alimentação** conectada
- **Redefina BIOS** para padrões de fábrica

### Windows não inicia
- **Verifique ordem de boot** na BIOS
- **Execute reparo de inicialização**:
  - Boot com mídia de instalação do Windows
  - "Solucionar problemas" → "Reparo de inicialização"

### SSD não é reconhecido
- **Verifique conexões físicas**
- **Teste em outro PC** se possível
- **Atualize drivers** da placa-mãe

### Partição não expandiu
1. **Abra Gerenciador de Disco**
2. **Clique direito** na partição principal
3. **Selecione "Estender Volume"**
4. **Siga o assistente**

### Problemas Específicos do Clonezilla

#### Clonezilla não reconhece disco
- **Verifique** se o disco está conectado corretamente
- **Use adaptador USB diferente** se aplicável
- **Reinicie** o Clonezilla e tente novamente

#### Erro durante clonagem
- **Verifique** se há espaço suficiente no destino
- **Execute** verificação de disco no Windows antes da clonagem
- **Tente** modo `Expert` com opções específicas

#### Boot não funciona após clonagem
- **Verifique** ordem de boot na BIOS
- **Execute** reparo de inicialização do Windows
- **Recrie** a clonagem usando opção `-k1` (expandir partições)




---

## Sobre

By: William Pilger

**Tempo estimado**: 2-4 horas (incluindo clonagem)  
**Dificuldade**: Intermediária  
**Risco**: Baixo (se seguidas as precauções)

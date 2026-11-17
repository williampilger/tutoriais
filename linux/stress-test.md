# Teste de stress no Linux (CPU, GPU, memória e disco)

Guia rápido para colocar carga no sistema: validar refrigeração, estabilidade, fonte, ou reproduzir problemas que só aparecem sob carga.

> ⚠️ **Atenção:** stress de verdade esquenta e pode travar a máquina, principalmente se o hardware já estiver com problema. Sempre monitore as temperaturas (veja [Monitoramento](#monitoramento)) e saiba como parar (`Ctrl+C` ou `pkill stress-ng`).

---

## TL;DR

```bash
sudo apt install stress-ng s-tui fio     # Debian/Ubuntu

stress-ng --cpu 0 --timeout 10m                      # CPU (todos os núcleos)
stress-ng --vm 2 --vm-bytes 80% --timeout 10m        # Memória
stress-ng --hdd 2 --timeout 10m                      # Disco
glmark2   # ou gpu-burn (NVIDIA)                     # GPU
```

---

## Instalação

| Distro | Comando |
|---|---|
| Debian / Ubuntu / Mint / Zorin | `sudo apt install stress-ng s-tui fio lm-sensors glmark2` |
| Fedora | `sudo dnf install stress-ng s-tui fio lm_sensors glmark2` |
| Arch | `sudo pacman -S stress-ng s-tui fio lm_sensors glmark2` |

Depois de instalar o `lm-sensors`, rode uma vez:

```bash
sudo sensors-detect --auto
```

---

## CPU

### Opção 1 — `stress-ng` (recomendado)

```bash
# Todos os núcleos (0 = auto), por 10 minutos
stress-ng --cpu 0 --timeout 10m

# 4 workers, mostrando métricas no final
stress-ng --cpu 4 --timeout 5m --metrics-brief

# Carga mais "pesada" (aquece mais): operações de matriz
stress-ng --cpu 0 --cpu-method matrixprod --timeout 10m

# Limitar a 50% de carga em cada núcleo
stress-ng --cpu 0 --cpu-load 50 --timeout 10m
```

### Opção 2 — `s-tui` (interface + stress + gráficos)

```bash
s-tui
```

Abre um painel no terminal com frequência, uso, temperatura e consumo. Mude de **Monitor** para **Stress** no menu à esquerda para iniciar a carga. É a forma mais prática de ver tudo ao mesmo tempo.

### Opção 3 — sem instalar nada

```bash
# Um processo "yes" por núcleo
for i in $(seq $(nproc)); do yes > /dev/null & done

# Parar
pkill yes
```

---

## Memória (RAM)

```bash
# 2 workers alocando juntos 80% da RAM disponível
stress-ng --vm 2 --vm-bytes 80% --timeout 10m

# Com verificação dos dados escritos (detecta erro de memória)
stress-ng --vm 2 --vm-bytes 80% --verify --timeout 10m
```

> Não passe de ~90%: o OOM killer vai começar a matar processos (inclusive o seu desktop).

### Testar se a RAM tem defeito

O `stress-ng` estressa, mas não é um teste de memória completo. Para isso:

```bash
sudo apt install memtester
sudo memtester 4G 3      # testa 4 GB, 3 passadas
```

Para teste completo (sem o sistema rodando), use o **MemTest86+** no boot (geralmente já aparece no GRUB do Ubuntu, ou grave um pendrive).

---

## Disco

### Opção 1 — `stress-ng`

```bash
# 2 workers escrevendo/lendo arquivos no diretório atual
stress-ng --hdd 2 --hdd-bytes 1G --timeout 10m

# Rodar em um disco específico: execute dentro do ponto de montagem
cd /mnt/meudisco && stress-ng --hdd 2 --timeout 10m
```

### Opção 2 — `fio` (benchmark de verdade)

```bash
# Escrita sequencial
fio --name=seqwrite --rw=write --bs=1M --size=2G --numjobs=1 --direct=1 --filename=./fio.test

# Leitura aleatória 4K (o que mais importa no dia a dia)
fio --name=randread --rw=randread --bs=4k --size=2G --numjobs=4 --iodepth=32 \
    --ioengine=libaio --direct=1 --runtime=60 --time_based --group_reporting --filename=./fio.test

# Limpar
rm ./fio.test
```

### Opção 3 — `dd` (sem instalar nada)

```bash
# Escrita (ignora cache com oflag=direct)
dd if=/dev/zero of=./teste.img bs=1M count=4096 oflag=direct status=progress

# Leitura
dd if=./teste.img of=/dev/null bs=1M iflag=direct status=progress

rm ./teste.img
```

> ⚠️ **Nunca** aponte `of=` para um dispositivo (`/dev/sda`, `/dev/nvme0n1`): isso apaga o disco. Sempre use um arquivo.

### Saúde do disco

```bash
sudo apt install smartmontools
sudo smartctl -a /dev/nvme0n1     # ou /dev/sda
```

---

## GPU

### Qualquer GPU (OpenGL) — `glmark2`

```bash
glmark2                 # benchmark padrão
glmark2 --run-forever   # carga contínua (Ctrl+C para parar)
```

### Vulkan — `vkmark`

```bash
sudo apt install vkmark
vkmark
```

### NVIDIA — `gpu-burn` (stress pesado de CUDA)

Requer driver proprietário + CUDA toolkit.

```bash
git clone https://github.com/wilicc/gpu-burn
cd gpu-burn
make
./gpu_burn 600          # 600 segundos
```

Monitorar:

```bash
watch -n 1 nvidia-smi
```

### AMD

```bash
# Carga: glmark2 / vkmark (acima)
# Monitoramento:
sudo apt install radeontop
radeontop
```

Para GPUs AMD/Intel também funciona bem o `nvtop` (apesar do nome, suporta várias marcas):

```bash
sudo apt install nvtop
nvtop
```

### Alternativa gráfica

**Unigine Heaven / Superposition** (download no site da Unigine) — benchmarks 3D clássicos, rodam nativamente no Linux.

---

## Tudo ao mesmo tempo

```bash
stress-ng --cpu 0 --vm 2 --vm-bytes 70% --hdd 1 --timeout 15m --metrics-brief
```

E, em outro terminal, `glmark2 --run-forever` ou `gpu_burn` para a GPU. Isso é o mais próximo de "puxar a fonte no talo".

---

## Monitoramento

Deixe um destes rodando em outro terminal enquanto estressa:

| Ferramenta | O que mostra |
|---|---|
| `s-tui` | CPU: frequência, uso, temperatura, potência |
| `watch -n 1 sensors` | Temperaturas de todos os sensores |
| `htop` / `btop` | Uso de CPU e memória por processo |
| `iostat -x 1` (pacote `sysstat`) | Uso e latência dos discos |
| `nvtop` / `nvidia-smi` / `radeontop` | GPU |
| `sudo dmesg -w` | Erros do kernel (MCE, I/O, throttling) |

**Referências de temperatura (aproximadas):**
- CPU desktop: até ~85 °C sob carga é aceitável; acima de 95 °C a CPU começa a reduzir clock (throttling).
- GPU: até ~85 °C é normal sob carga.
- NVMe: acima de ~70 °C costuma começar a reduzir velocidade.

---

## Parar tudo

```bash
pkill stress-ng
pkill yes
pkill gpu_burn
```

---

## Resumo

| Alvo | Mais simples | Mais completo |
|---|---|---|
| CPU | `stress-ng --cpu 0` | `s-tui` |
| Memória | `stress-ng --vm 2 --vm-bytes 80%` | `memtester` / MemTest86+ |
| Disco | `stress-ng --hdd 2` / `dd` | `fio` + `smartctl` |
| GPU | `glmark2` | `gpu-burn` (NVIDIA) / Unigine |

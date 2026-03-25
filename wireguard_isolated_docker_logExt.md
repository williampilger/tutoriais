# Gerar Logs das conexões à VPN

Este "utilitário" tem como objetivo ajudar na geração e análise de logs de conexão com o Wireguard,
considerando que você configurou o Wireguard com base [neste guia](./wireguard_isolated_docker.md).

Por padrão, este container (nem o wireguard) não possui dados de LOG de quando cada cliente esteve conectado, então esta funcionalidade é um "adicional".

Esta ferramenta é fornecida em duas etapas:
- 1) Captura dos logs de conexões à VPN
- 2) Análise dos logs para gerar um relatório


## 1) Captura dos logs de conexões à VPN

Para capturar os logs de conexões à VPN, considere que o nome do container do Wireguard seja `wireguard`,
e então crie um script `.sh` com o seguinte conteúdo, que será executado periodicamente por uma cron:

*~/wireguard/scripts/capture_logs.sh*
```sh
#!/bin/bash
TS="$(date '+%F %T')"
docker exec wireguard wg show all dump | while IFS=$'\t' read -r iface pubkey psk endpoint allowedips handshake rx tx keepalive; do
  echo "$TS|$iface|$pubkey|$endpoint|$allowedips|$handshake|$rx|$tx" >> ~/wireguard/logs/peers.log
done
```

Agora, edite sua crontab para executar este script a cada 1 minuto, por exemplo:

```sh
* * * * * /home/usuario/wireguard/scripts/capture_logs.sh
```

## 2) Análise dos logs para gerar um relatório

Com os logs capturados, você pode criar um script para analisar os dados e gerar um relatório de conexões. Por exemplo:

*~/wireguard/scripts/analyze_logs.py*
```py
#!/usr/bin/env python3
# 2026-03-25 - William Pilger < GERADO POR IA

import argparse
import csv
from dataclasses import dataclass
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Tuple, Optional

import matplotlib.pyplot as plt
import matplotlib.dates as mdates


@dataclass
class Snapshot:
    collected_at: datetime
    iface: str
    pubkey: str
    endpoint: str
    allowed_ips: str
    handshake_epoch: int
    rx: int
    tx: int


def parse_args():
    parser = argparse.ArgumentParser(
        description="Gera gráfico de atividade dos peers WireGuard a partir do arquivo peers.log"
    )
    parser.add_argument(
        "--log",
        required=True,
        help="Caminho do arquivo peers.log",
    )
    parser.add_argument(
        "--map",
        help="CSV opcional com mapeamento pubkey,nome",
    )
    parser.add_argument(
        "--output",
        default=None,
        help="Arquivo PNG de saída (opcional). Se omitido, mostra o gráfico na tela.",
    )
    parser.add_argument(
        "--active-window",
        type=int,
        default=180,
        help="Janela em segundos para considerar o peer ativo após o latest_handshake",
    )
    parser.add_argument(
        "--min-duration",
        type=int,
        default=0,
        help="Ignora blocos de atividade menores que X segundos",
    )
    return parser.parse_args()


def load_name_map(path: Optional[str]) -> Dict[str, str]:
    if not path:
        return {}

    mapping: Dict[str, str] = {}
    with open(path, "r", encoding="utf-8", newline="") as f:
        reader = csv.reader(f)
        for row in reader:
            if not row or len(row) < 2:
                continue
            pubkey = row[0].strip()
            name = row[1].strip()
            if pubkey and name:
                mapping[pubkey] = name
    return mapping


def parse_line(line: str) -> Optional[Snapshot]:
    parts = line.strip().split("|")
    if len(parts) != 8:
        return None

    try:
        collected_at = datetime.strptime(parts[0], "%Y-%m-%d %H:%M:%S")
        iface = parts[1]
        pubkey = parts[2]
        endpoint = parts[3]
        allowed_ips = parts[4]
        handshake_epoch = int(parts[5].strip() or 0)
        rx = int(parts[6].strip() or 0)
        tx = int(parts[7].strip() or 0)

        return Snapshot(
            collected_at=collected_at,
            iface=iface,
            pubkey=pubkey,
            endpoint=endpoint,
            allowed_ips=allowed_ips,
            handshake_epoch=handshake_epoch,
            rx=rx,
            tx=tx,
        )
    except Exception:
        return None


def load_snapshots(path: str) -> List[Snapshot]:
    snapshots: List[Snapshot] = []

    with open(path, "r", encoding="utf-8") as f:
        for line in f:
            if not line.strip():
                continue
            snap = parse_line(line)
            if snap is not None:
                snapshots.append(snap)

    snapshots.sort(key=lambda s: (s.pubkey, s.collected_at))
    return snapshots


def is_active(snapshot: Snapshot, active_window: int) -> bool:
    if snapshot.handshake_epoch <= 0:
        return False

    handshake_time = datetime.fromtimestamp(snapshot.handshake_epoch)
    delta = (snapshot.collected_at - handshake_time).total_seconds()

    return 0 <= delta <= active_window


def build_activity_intervals(
    snapshots: List[Snapshot],
    active_window: int,
    min_duration: int,
) -> Dict[str, List[Tuple[datetime, datetime]]]:
    per_peer: Dict[str, List[Snapshot]] = {}
    for snap in snapshots:
        per_peer.setdefault(snap.pubkey, []).append(snap)

    result: Dict[str, List[Tuple[datetime, datetime]]] = {}

    for pubkey, peer_snaps in per_peer.items():
        peer_snaps.sort(key=lambda s: s.collected_at)

        intervals: List[Tuple[datetime, datetime]] = []
        current_start: Optional[datetime] = None
        current_end: Optional[datetime] = None

        for snap in peer_snaps:
            active = is_active(snap, active_window)

            if active:
                if current_start is None:
                    current_start = snap.collected_at
                    current_end = snap.collected_at
                else:
                    current_end = snap.collected_at
            else:
                if current_start is not None and current_end is not None:
                    duration = (current_end - current_start).total_seconds()
                    if duration >= min_duration:
                        intervals.append((current_start, current_end))
                    current_start = None
                    current_end = None

        if current_start is not None and current_end is not None:
            duration = (current_end - current_start).total_seconds()
            if duration >= min_duration:
                intervals.append((current_start, current_end))

        result[pubkey] = intervals

    return result


def shorten_pubkey(pubkey: str) -> str:
    if len(pubkey) <= 14:
        return pubkey
    return f"{pubkey[:6]}...{pubkey[-6:]}"


def plot_activity(
    intervals_by_peer: Dict[str, List[Tuple[datetime, datetime]]],
    name_map: Dict[str, str],
    output_path: Optional[str],
):
    peers = [p for p, intervals in intervals_by_peer.items() if intervals]
    peers.sort(key=lambda p: name_map.get(p, p))

    if not peers:
        fig, ax = plt.subplots(figsize=(12, 4))
        ax.axis("off")
        ax.text(
            0.5,
            0.5,
            "Nenhum intervalo de atividade encontrado\n"
            "Ajuste --active-window ou verifique se houve handshakes recentes.",
            ha="center",
            va="center",
            fontsize=12,
        )
        plt.tight_layout()
        if output_path:
            plt.savefig(output_path, dpi=200)
            print(f"Gráfico salvo em: {output_path}")
        else:
            plt.show()
            print("Gráfico exibido na tela.")
        return False

    fig_height = max(4, 0.7 * len(peers) + 1.5)
    fig, ax = plt.subplots(figsize=(15, fig_height))

    y_positions = list(range(len(peers)))
    labels: List[str] = []

    for y, pubkey in enumerate(peers):
        label = name_map.get(pubkey, shorten_pubkey(pubkey))
        labels.append(label)

        bars = []
        for start, end in intervals_by_peer[pubkey]:
            start_num = mdates.date2num(start)
            duration_num = mdates.date2num(end) - start_num

            # evita barra invisível se houver só 1 ponto
            if duration_num == 0:
                duration_num = 1 / (24 * 60)  # 1 minuto

            bars.append((start_num, duration_num))

        ax.broken_barh(bars, (y - 0.35, 0.7))

    ax.set_yticks(y_positions)
    ax.set_yticklabels(labels)
    ax.set_xlabel("Horário")
    ax.set_ylabel("Peer")
    ax.set_title("Atividade dos peers WireGuard")

    ax.xaxis.set_major_formatter(mdates.DateFormatter("%d/%m %H:%M"))
    fig.autofmt_xdate()

    ax.grid(True, axis="x", alpha=0.3)
    plt.tight_layout()
    if output_path:
        plt.savefig(output_path, dpi=200)
        print(f"Gráfico salvo em: {output_path}")
    else:
        plt.show()
        print("Gráfico exibido na tela.")
    return True


def print_activity_hint(snapshots: List[Snapshot]) -> None:
    if not snapshots:
        print("Nenhum snapshot válido foi encontrado no log.")
        return

    positive_deltas = []
    for snap in snapshots:
        if snap.handshake_epoch <= 0:
            continue
        handshake_time = datetime.fromtimestamp(snap.handshake_epoch)
        delta = (snap.collected_at - handshake_time).total_seconds()
        if delta >= 0:
            positive_deltas.append(delta)

    if not positive_deltas:
        print("Nenhum peer com latest_handshake válido (> 0) foi encontrado.")
        return

    best = int(min(positive_deltas))
    print(
        "Sem atividade na janela atual. "
        f"Menor diferença coletado-handshake encontrada: {best}s."
    )
    print(
        f"Dica: tente um --active-window maior que {best} (ex.: {best + 60})."
    )


def main():
    args = parse_args()

    log_path = Path(args.log)
    if not log_path.exists():
        raise FileNotFoundError(f"Arquivo de log não encontrado: {log_path}")

    name_map = load_name_map(args.map)
    snapshots = load_snapshots(str(log_path))
    intervals = build_activity_intervals(
        snapshots=snapshots,
        active_window=args.active_window,
        min_duration=args.min_duration,
    )
    has_data = plot_activity(intervals, name_map, args.output)
    if not has_data:
        print_activity_hint(snapshots)


if __name__ == "__main__":
    main()
```

### Uso

Para usar o script de análise, execute o seguinte comando, apontando para o arquivo `peers.log` gerado pelo script de captura:

```sh
python3 analyze_logs.py --log /home/usuario/wireguard/logs/peers.log --map /home/usuario/wireguard/logs/pubkey_name_map.csv
```
O arquivo `pubkey_name_map.csv` é opcional e deve conter linhas no formato `pubkey,nome` para mapear as chaves públicas dos peers para nomes mais amigáveis no gráfico.

Exemplo de CSV de mapeamento

```csv
pubkey1,Peer A
pubkey2,Peer B
pubkey3,Peer C
```

Se quiser gerar uma imagem PNG do gráfico em vez de exibi-lo na tela, adicione a opção `--output`:

```sh
python3 analyze_logs.py --log /home/usuario/wireguard/logs/peers.log --output ./saida.png
```

Se quiser modificar parâmetros de tempo limite, use as flags `--active-window` e `--min-duration`:

```sh
python3 analyze_logs.py --log /home/usuario/wireguard/logs/peers.log --active-window 300 --min-duration 60
```

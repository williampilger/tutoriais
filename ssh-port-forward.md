# Tunel para encaminhamento de porta pelo SSH

Pra direcionar a porta `5555`, por exemplo, do host remoto para o localhost:

> ssh -N -L 5555:127.0.0.1:5555 user@host

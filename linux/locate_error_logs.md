# Localizar logs de erros no linux

Quando você recebe um erro sem muita especificação, como o `killed`, que não especifica o motivo, pode encontrar mais informações usando:

> grep -i "killed" /var/log/syslog

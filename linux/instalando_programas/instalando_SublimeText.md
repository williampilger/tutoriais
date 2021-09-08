# Instalando o Sublime Text e Sublime Merge

# Usando APT

```
wget -qO - https://download.sublimetext.com/sublimehq-pub.gpg | sudo apt-key add -
sudo apt-get install apt-transport-https
echo "deb https://download.sublimetext.com/ apt/stable/" | sudo tee /etc/apt/sources.list.d/sublime-text.list
sudo apt-get update
sudo apt-get install sublime-text
sudo apt-get install sublime-merge
```

# Usando Snap

```
snap install sublime-text --classic
snap install sublime-merge --classic
```

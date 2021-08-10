#FALHOU
#sudo su
wget -qO- https://packages.microsoft.com/keys/microsoft.asc | sudo apt-key add -
sudo add-apt-repository "$(wget -qO- https://packages.microsoft.com/config/ubuntu/20.04/mssql-server-2019.list)"
sudo apt-get update
sudo apt-get install -f -y mssql-server
sudo /opt/mssql/bin/mssql-conf setup

sudo apt install -f -y curl
curl https://packages.microsoft.com/keys/microsoft.asc | sudo apt-key add -
curl https://packages.microsoft.com/config/ubuntu/20.04/prod.list | sudo tee /etc/apt/sources.list.d/msprod.list

sudo apt-get install -f -y mssql-tools unixodbc-dev
sudo apt-get install -f -y mssql-tools
echo 'export PATH="$PATH:/opt/mssql-tools/bin"' >> ~/.bash_profile
echo 'export PATH="$PATH:/opt/mssql-tools/bin"' >> ~/.bashrc
source ~/.bashrc

#sqlcmd -S localhost -U SA -P '<YourPassword>' #Use isso para Conectar ao seu servidor
#Retirado de: https://docs.microsoft.com/pt-br/sql/linux/quickstart-install-connect-ubuntu?view=sql-server-ver15

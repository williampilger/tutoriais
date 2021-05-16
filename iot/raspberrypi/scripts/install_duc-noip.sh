cd /usr/local/src/
wget http://www.noip.com/client/linux/noip-duc-linux.tar.gz
tar xf noip-duc-linux.tar.gz
cd noip-*
make install
cd ..
rm -rf noip-*
rm noip-duc-linux.tar.gz

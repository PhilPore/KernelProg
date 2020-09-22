#!/bin/bash
sudo apt update


echo $(curl -L https://sourceforge.net/projects/lxr/files/latest/download -o lxr-2.3.5.tgz)

sudo apt-get install perl -y
sudo apt-get install apache2 -y
sudo apt-get install apache2-mod-perl
sudo apt-get install exuberant-ctags -y

sudo apt-get install mysql-server -y
sudo apt-get install libmysqlclient-dev -y
sudo apt-get install libdbd-mysql-perl -y

sudo apt-get libapache2-mod-perl2 -y
#get the glimpse db up

sudo apt-get install glimpse -y
sudo apt install libfile-mmagic-perl
sudo cpan DBI
sudo cpan File::MMagic
sudo cpan DBD::mysql

mkdir LXRinst
echo "Enter the source directory you want to use for the install."
read sr 
mkdir -p $sr/v1
cd $sr
echo "This will be the directory you use as your source directory: "
echo $(pwd)
cd ..
echo "-------------------------"
echo "Name of Glimpse DB directory you want to make?"
read gl 
mkdir $gl
cd $gl
echo "This will your Glimpse DB directory: "
echo $(pwd)
cd ..
echo "-------------------------"

tar -zxf lxr-2.3.5.tgz 
mv lxr-2.3.5 LXRinst
cd LXRinst/lxr-2.3.5
#begins configuration
sudo ./scripts/configure-lxr.pl -vv
sudo ./custom.d/initdb.sh
cp custom.d/lxr.conf .
sudo ./genxref --url=http://localhost/lxr --version=v1 --checkonly
#ges the site going.
sudo cp custom.d/apache-lxrserver.conf /etc/apache2/conf-available
sudo a2enconf apache-lxrserver.conf
sudo apache2ctl restart

echo "Now, go to http://localhost/lxr/source and everything should be in order. Be sure to install the kernel you want in the v1 folder, and then run: sudo ./genxref --url==http://localhost/lxr --version=v1"

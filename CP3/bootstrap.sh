#!/usr/bin/env bash

# Upgrade the package installer
sudo apt-get -y upgrade

# Update package manager
sudo apt-get update

# Common Packages
sudo apt-get install -y build-essential tcl tk --no-install-recommends
sudo apt-get install -y libpq-dev vim --no-install-recommends
sudo apt-get install -y software-properties-common python-software-properties

# Oracle Java 8
echo oracle-java8-installer shared/accepted-oracle-license-v1-1 select true | sudo /usr/bin/debconf-set-selections
sudo add-apt-repository ppa:webupd8team/java -y
sudo apt-get update
sudo apt-get install oracle-java8-installer
sudo apt-get install -y oracle-java8-set-default

# Scala 2.12.2
wget www.scala-lang.org/files/archive/scala-2.12.2.deb
sudo dpkg -i scala-2.12.2.deb

# SBT 0.13.15
wget -c https://bintray.com/artifact/download/sbt/debian/sbt-0.13.15.deb
sudo dpkg -i sbt-0.13.15.deb
sudo apt-get update
sudo apt-get install sbt

# jq
sudo apt-get install -y jq
sudo apt-get update

# Octave & GNUPlot
sudo add-apt-repository -y ppa:octave/stable
sudo apt-get update
sudo apt-get -y install octave liboctave-dev gnuplot --no-install-recommends

# Apache ActiveMQ 5.14.0
wget https://archive.apache.org/dist/activemq/5.14.0/apache-activemq-5.14.0-bin.tar.gz
tar -C /home/ubuntu -zxvf apache-activemq-5.14.0-bin.tar.gz

# DOS2Unix
# sudo apt-get install -y dos2unix

# Cleanup Install Artifacts
sudo rm -f scala-2.12.2.deb
sudo rm -f sbt-0.13.15.deb
sudo rm -f apache-activemq-5.14.0-bin.tar.gz

# Clean up previous logs / scenarios
sudo rm -f princess.log
sudo rm -f scenario.json

# Access Control Settings
sudo chmod -R 777 ./apache-activemq-5.14.0
sudo chmod 777 ./start
sudo chmod 777 ./grizzly-service.sh
sudo chmod 777 ./run

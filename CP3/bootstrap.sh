#!/usr/bin/env bash

# Configure system for Java
export JAVA_HOME=/usr/java/jdk1.8.0_211
export PATH=$PATH:$JAVA_HOME/bin
update-alternatives --install "/usr/bin/java" "java" "/usr/java/jdk1.8.0_211/bin/java" 1
update-alternatives --install "/usr/bin/javac" "javac" "/usr/java/jdk1.8.0_211/bin/javac" 1
update-alternatives --install "/usr/bin/javaws" "javaws" "/usr/java/jdk1.8.0_211/bin/javaws" 1
update-alternatives --set java /usr/java/jdk1.8.0_211/bin/java
update-alternatives --set javac /usr/java/jdk1.8.0_211/bin/javac
update-alternatives --set javaws /usr/java/jdk1.8.0_211/bin/javaws

# Upgrade the package installer
apt-get -y upgrade

# Update package manager
apt-get update

# Common Packages
apt-get install -y build-essential tcl tk --no-install-recommends
apt-get install -y libpq-dev vim --no-install-recommends
apt-get install -y software-properties-common python-software-properties
apt-get install -f -y


# Scala 2.12.2
wget www.scala-lang.org/files/archive/scala-2.12.2.deb
dpkg -i scala-2.12.2.deb

# SBT 0.13.15
wget -c https://bintray.com/artifact/download/sbt/debian/sbt-0.13.15.deb
dpkg -i sbt-0.13.15.deb
apt-get update
apt-get install sbt
apt-get install -f -y

# jq
apt-get install -y jq
apt-get update
apt-get install -f -y

# Octave & GNUPlot
add-apt-repository -y ppa:octave/stable
apt-get update
apt-get -y install octave liboctave-dev gnuplot --no-install-recommends
apt-get install -f -y

# Apache ActiveMQ 5.14.0
wget https://archive.apache.org/dist/activemq/5.14.0/apache-activemq-5.14.0-bin.tar.gz
tar -C /cp3 -zxvf apache-activemq-5.14.0-bin.tar.gz

# DOS2Unix
# apt-get install -y dos2unix

# Cleanup Install Artifacts
rm -f scala-2.12.2.deb
rm -f sbt-0.13.15.deb
rm -f apache-activemq-5.14.0-bin.tar.gz

# Clean up previous logs / scenarios
rm -f princess.log
rm -f scenario.json

# Access Control Settings
chmod -R 777 ./apache-activemq-5.14.0
chmod 777 ./start
chmod 777 ./grizzly-service.sh
chmod 777 ./run

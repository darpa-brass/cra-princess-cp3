FROM ubuntu:16.04
MAINTAINER Tim Meunier <timothy.meunier@ll.mit.edu>
# Install system tools
ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get -y install locales unzip tar wget curl software-properties-common apt-transport-https
RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8
#  set up licenses for oracle java
RUN add-apt-repository -y ppa:webupd8team/java
RUN echo "deb https://dl.bintray.com/sbt/debian /" | tee -a /etc/apt/sources.list.d/sbt.list
RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv 2EE0EA64E40A89B84B2DF73499E82A75642AC823
RUN apt-get update
RUN echo debconf shared/accepted-oracle-license-v1-1 select true | debconf-set-selections
RUN echo debconf shared/accepted-oracle-license-v1-1 seen true | debconf-set-selections
RUN apt-get -y install oracle-java8-installer --no-install-recommends
RUN apt-get install -y sbt

FROM ubuntu:16.04
ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update
RUN apt-get install -y wget sudo software-properties-common apt-transport-https
RUN useradd -m ubuntu
RUN echo "Defaults\tenv_keep += \"DEBIAN_FRONTEND http_proxy https_proxy HTTP_PROXY HTTPS_PROXY no_proxy NO_PROXY\"" >> /etc/sudoers.d/proxy
RUN echo "Defaults:ubuntu !requiretty" >> /etc/sudoers.d/vagrant
RUN echo "ubuntu\tALL=(ALL)\tNOPASSWD: ALL" >> /etc/sudoers.d/vagrant
ADD . /home/ubuntu
RUN find /home/ubuntu -name "*.sh" -exec chmod +x {} \;
USER ubuntu
WORKDIR /home/ubuntu 
RUN ./bootstrap.sh

FROM ubuntu:16.04

# If you are LL you probably want to uncomment these
# (borrowed from the harness dockerfiles)
#ENV http_proxy "http://llproxy:8080"
#ENV https_proxy "http://llproxy:8080"

#
# note that we're specifically using the system compiler shipped by
# ubuntu to validate the csmith outputs.
#

RUN apt-get -y update && apt-get -y install \
	wget=1.17.1-1ubuntu1.4 \
	build-essential=12.1ubuntu2 \
	libc6-dev-i386=2.23-0ubuntu10 \
	m4=1.4.17-5 \
	python3=3.5.1-3

USER root

# NOTE NOTE NOTE
# for docker reasons, the uid must match your uid outside the container
# edit as needed. (don't know how to make this go automatically)
RUN adduser -q --disabled-password --gecos "csmith" --uid 1002 csmith

RUN mkdir /csmith /corpus /corpus/failed
RUN chown csmith /csmith /corpus
USER csmith

# download csmith
WORKDIR /csmith
RUN wget https://github.com/csmith-project/csmith/archive/csmith-2.3.0.tar.gz

# compile csmith
COPY ./scripts /csmith/scripts
RUN /csmith/scripts/docompile.sh

# copy the filters (after compiling csmith, to avoid doing that more than
# necessary)
COPY ./filters /csmith/filters

# and off we go
# arguments are: seed and number of tests to generate
CMD ["/csmith/scripts/dogenerate.sh", "12345", "100"]


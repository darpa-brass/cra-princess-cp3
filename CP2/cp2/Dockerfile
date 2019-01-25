#FROM python:3.6
#FROM ubuntu:16.04
# docker pull ocaml/opam:ubuntu-16.04_ocaml-4.06.0
FROM ocaml/opam:ubuntu-16.04_ocaml-4.06.0

# If you are LL you probably want to uncomment these
# (borrowed from the harness dockerfiles)
#ENV http_proxy "http://llproxy:8080"
#ENV https_proxy "http://llproxy:8080"

USER opam
RUN opam switch 4.06.0
#
# Install ocaml packages.
#
# bintools/gentarget uses:
#    num
# cassiopeia uses:
#    ocamlbuild
#    ocamlfind
#    num (?)
#    menhir
#    batteries
#
RUN opam install batteries ocamlbuild ocamlfind num menhir

USER root

#
# install:
#   - python3 for the python sut code in sut/
#   - bmake for builds
#   - qemu for running test programs
#   - wget to fetch things we have to compile
#
RUN apt-get -y update && apt-get -y install \
	python3=3.5.1-3 \
	python3-pip=8.1.1-2ubuntu0.4 \
	bmake=20160220-2 \
	qemu=1:2.5+dfsg-5ubuntu10.30 \
	wget=1.17.1-1ubuntu1.4

#
# install jsonobject, requests, and flask with pip
# these should really be given fixed version numbers...
#
ENV PYTHONPATH $PYTHONPATH:/cp2/sut
#RUN pip install --upgrade pip
#RUN pip install jsonobject requests
RUN pip3 install --upgrade pip
RUN pip3 install jsonobject requests
# jsonobject takes forever to fetch, so make a separate thing for flask
RUN pip3 install flask

# install crosscompiler environment for testing bintools
COPY ./cross /cp2/cross
RUN sh /cp2/cross/prep-install-cross.sh arm sparc64

# Note: installing the crosscompilers takes long enough to be annoying,
# so don't move anything that changes much above this point.

# install packages needed for racket and rosette
RUN apt-get -y install fontconfig=2.11.94-0ubuntu1.1 libcairo2=1.14.6-1 libpango1.0-dev=1.38.1-1

# install racket and rosette (and boolector, and uclibc)
# note: rosette specifically requires racket 6.6
#COPY ./software /cp2/software
RUN mkdir /cp2/software
COPY ./software/prep-download.sh /cp2/software/prep-download.sh
RUN sh /cp2/software/prep-download.sh
COPY ./software/prep-build.sh /cp2/software/prep-build.sh
RUN sh /cp2/software/prep-build.sh
COPY ./software/prep-build2.sh /cp2/software/prep-build2.sh
COPY ./software/uclibc-config-sparc64 /cp2/software/uclibc-config-sparc64
COPY ./software/uclibc-config-arm /cp2/software/uclibc-config-arm
RUN sh /cp2/software/prep-build2.sh

# copy in the trees (our code)
COPY ./trees /cp2/trees

# build the trees
RUN sh /cp2/trees/prep-build.sh

# copy the test snippets
COPY ./snippets /cp2/snippets
# and the toolchain test corpus
COPY ./corpus /cp2/corpus

# add the rest of the scripts
COPY ./toolchain /cp2/toolchain
COPY ./synth /cp2/synth
COPY ./sut /cp2/sut

# and off we go
WORKDIR /cp2/sut
CMD ["python3", "main.py"]
EXPOSE 8082

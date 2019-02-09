# Sample makefile for programs that use the ROSE library.
#
# ROSE has a number of configuration details that must be present when
# compiling and linking a user program with ROSE, and some of these
# details are difficult to get right.  The most foolproof way to get
# these details into your own makefile is to use the "rose-config"
# tool.
#
#
# This makefile assumes:
#   1. The ROSE library has been properly installed (refer to the
#      documentation for configuring, building, and installing ROSE).
#
#   2. The top of the installation directory is $(ROSE_INSTALLED). This
#      is the same directory you specified for the "--prefix" argument
#      of the "configure" script, or the "CMAKE_INSTALL_PREFIX" if using
#      cmake. E.g., "/usr/local".
#
# The "rose-config" tool currently only works for ROSE configured with
# GNU auto tools (e.g., you ran "configure" when you built and
# installed ROSE). The "cmake" configuration is not currently
# supported by "rose-config" [September 2015].
##############################################################################
ROSE_INSTALLED=/home/gfry/dev/ROSE/rose-installation
# Standard C++ compiler stuff (see rose-config --help)
CXX      = g++ #$(shell $(ROSE_INSTALLED)/bin/rose-config --config $(ROSE_INSTALLED)/lib/rose-config.cfg cxx)
CPPFLAGS = $(shell $(ROSE_INSTALLED)/bin/rose-config --config $(ROSE_INSTALLED)/lib/rose-config.cfg cppflags) -I$(ROSE_INSTALLED)/include/rose
CXXFLAGS = $(shell $(ROSE_INSTALLED)/bin/rose-config --config $(ROSE_INSTALLED)/lib/rose-config.cfg cxxflags)
LDFLAGS  = $(shell $(ROSE_INSTALLED)/bin/rose-config --config $(ROSE_INSTALLED)/lib/rose-config.cfg ldflags)
LIBDIRS  = $(shell $(ROSE_INSTALLED)/bin/rose-config --config $(ROSE_INSTALLED)/lib/rose-config.cfg libdirs)
 
MOSTLYCLEANFILES =
 
##############################################################################
# Assuming your source code is "demo.C" to build an executable named "demo".
 
all: transform 

transform.o: transform.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $^

transform: transform.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Remember to set:"
	@echo "  LD_LIBRARY_PATH=$(LIBDIRS):$$LD_LIBRARY_PATH"

MOSTLYCLEANFILES += tranform transform.o
 
##############################################################################
# Standard boilerplate
 
.PHONY: clean
clean:
	rm -f $(MOSTLYCLEANFILES)

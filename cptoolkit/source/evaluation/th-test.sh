#!/bin/bash -eu

./th.sh READY
./th.sh PERTURBATION
./th.sh ADAP_STARTED
./th.sh ADAP_COMPLETED
./th.sh RESULTS /test/results.csv
./th.sh CHECKSUM 0
./th.sh INTENT true
./th.sh INTENT false
./th.sh DATA_ERROR "Error in data format"
./th.sh DONE 10.0 5/20/2016 5/20/2017
./th.sh STOPPED

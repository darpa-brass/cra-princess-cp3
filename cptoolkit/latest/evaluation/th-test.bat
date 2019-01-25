@echo off

call th READY
call th PERTURBATION
call th ADAP_STARTED
call th ADAP_COMPLETED
call th RESULTS \test\results.csv
call th CHECKSUM 0
call th INTENT true
call th INTENT false
call th DATA_ERROR "Error in data format"
call th DONE 10.0 5/20/2016 5/20/2017
call th STOPPED

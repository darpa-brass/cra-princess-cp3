#!/bin/bash
filename=$1
res=`cat $filename`
./th.sh READY
cp  $filename /test/target_reconst_file.json	

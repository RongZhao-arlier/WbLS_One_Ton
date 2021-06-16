#!/bin/bash
for currentnum in {1..30}
do
  echo "Number: $currentnum"
	rm testRatVector_v2_onlyforHodoTriggers
	lastnum=$(($currentnum-1))
	echo $lastnum
#	sed -i "s/245+${lastnum}e6/245+${currentnum}e6/g" ../src/CRYUtils.cc
	cd /public/users/zhaoy/softwares/cry_v1.7
	make
	cd testbak0110
	make testRatVector_v2_onlyforHodoTriggers
	./testRatVector_v2_onlyforHodoTriggers setupBNL1T.file 100000000 out_20210123_$currentnum.dat out_20210123_time_$currentnum.dat
done

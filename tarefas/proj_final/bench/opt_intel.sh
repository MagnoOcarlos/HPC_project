#!/bin/bash
#source ~/intel/oneapi/setvars.sh
cd ../../../proj_mag/src/
TIMEFORMAT=%R

###### opt 0 #######
for i in $(seq 0 3)
do
	icpc *.cpp *.h -O$i
	PROC_TIME=$(time (./a.out >/dev/null 2>&1)2>&1)
	echo -e $i '\t' $PROC_TIME>>../../tarefas/proj_final/bench/intel_opt0.dat	
done

rm a.out 
rm injection* arrive* 

##### opt 1 #######

for i in $(seq 0 3)
do
	icpc *.cpp *.h -w -mp1 -zero -xHOST -O$i 
	PROC_TIME=$(time (./a.out >/dev/null 2>&1)2>&1)
	echo -e $i '\t' $PROC_TIME>>../../tarefas/proj_final/bench/intel_opt1.dat	
done 


rm a.out 
rm injection* arrive* 



##### opt 2 ####


for i in $(seq 0 3)
do
	icpc *.cpp *.h -w -mp1 -zero -xHOST -fast=2 -O$i 
	PROC_TIME=$(time (./a.out >/dev/null 2>&1)2>&1)
	echo -e $i '\t' $PROC_TIME>>../../tarefas/proj_final/bench/intel_opt2.dat	
done 


rm a.out 
rm injection* arrive* 




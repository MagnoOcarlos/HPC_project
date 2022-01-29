#!/bin/bash

cd ../../../proj_mag/src/
TIMEFORMAT=%R

###### opt 0 #######
for i in $(seq 0 3)
do
	g++ *.cpp *.h -O$i
	PROC_TIME=$(time (./a.out >/dev/null 2>&1)2>&1)
	echo -e $i '\t' $PROC_TIME>>../../tarefas/proj_final/bench/gnu_opt0.dat	
done

rm a.out 
rm injection* arrive* 

##### opt 1 #######

for i in $(seq 0 3)
do
	g++ *.cpp *.h -O$i -fexpensive-optimizations -m64 -foptimize-register-move -funroll-loops -ffast-math -mtune=native -march=native
	PROC_TIME=$(time (./a.out >/dev/null 2>&1)2>&1)
	echo -e $i '\t' $PROC_TIME>>../../tarefas/proj_final/bench/gnu_opt1.dat	
done 


rm a.out 
rm injection* arrive* 



##### opt 2 ####


for i in $(seq 0 3)
do
	g++ *.cpp *.h -O$i -fexpensive-optimizations -m64 -foptimize-register-move -funroll-loops -ffast-math -mtune=haswell -march=haswell
	PROC_TIME=$(time (./a.out >/dev/null 2>&1)2>&1)
	echo -e $i '\t' $PROC_TIME>>../../tarefas/proj_final/bench/gnu_opt2.dat	
done 


rm a.out 
rm injection* arrive* 




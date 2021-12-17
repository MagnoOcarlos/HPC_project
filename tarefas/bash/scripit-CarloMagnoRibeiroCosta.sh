#!/bin/bash
#################################################################
	#Charge difference for 3 densities
       	#Author:Carlos Magno Ribeiro da Costa
	#e-mail:magno_costa@id.uff.br
        #How to run : type 'bash scriptCarlosMagnoRibeiroCosta.sh
	# nov/2021	
################################################################


#at first, lets define the number of rows using wc -l and awk
wc -l molecule.xsf > aux.txt # Assuming all the files have the same number of rows

n_rows=$(awk '{print $1}' aux.txt)
rm aux.txt 
final=3
beginning=104

h=$(expr $n_rows - $final)  #The variable h save the number of rows that the command head will read 
t=$(expr $h - $beginning) #The variable t save the number of rows that the command tail will read 

#creating the files with the right matrix from the .xsf files
head -n $h molecule.xsf | tail -n $t  >molecule.txt
head -n $h device.xsf | tail -n $t >device.txt
head -n $h devmol.xsf | tail -n $t >devmol.txt

#Pasting two files side by side in only one file, the second file begins at the column $7
paste molecule.txt device.txt | awk '{ print $1 +$7 " " $2+$8 " " $3+$9 " " $4+$10 " "$5+$11 " " $6+$12;}' > sum.txt

paste devmol.txt sum.txt | awk '{ print $1 -$7 " " $2-$8 " " $3-$9 " " $4-$10 " " $5-$11 " " $6-$12;}' > FinalMatrix.txt

#append the first lines from devmol.xsf in final result
head -n $beginning devmol.xsf  >finalResult.xsf


#append the FinalMatrix.txt in final result
cat FinalMatrix.txt >>finalResult.xsf

#adding the final lines from devmol.xsf in final result
tail -n $final  devmol.xsf >>finalResult.xsf

rm molecule.txt device.txt devmol.txt sum.txt FinalMatrix.txt #removing all non necessary files


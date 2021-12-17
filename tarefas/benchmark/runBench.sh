
declare -a angs

g++ *.cpp

for((i=1; i<=10000000; i=i*10)) do
       # angs=(${angs[*]} "$i")
       ./a.out $i
done


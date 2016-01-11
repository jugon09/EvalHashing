#!/bin/bash

n=0
n_fin=10
programa=./hash
out=cerca_binaria_resultados.txt

rm $out

while [ $n -lt $n_fin ]
do
    q=$((($n * 100) / $n_fin))
    n=$(($n+1))
    echo -ne "\r$q %"
    ./generadorRandom < entrada.txt
    echo "========================" >> $out
    (/usr/bin/time -f "%U" $programa >> $out) &>> $out
done

echo ""
    

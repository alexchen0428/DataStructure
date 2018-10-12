#!/bin/zsh
size=(1 5 5000 8000 12000 20000 30000 40000 50000 60000)
for ((i=0; i<3; i++)); do
    for ((j=0; j<10; j++)); do
        s=${size[$j+1]}
        for ((k=0; k<s; k++)); do
            echo $i $k | ./test< ../inputs/$j.in >> ../outs/$i$j.out
        done
    done
done 
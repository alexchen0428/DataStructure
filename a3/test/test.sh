#!/bin/zsh
size=(1 300 600 1000 2000 3000)
for ((i=0; i<6; i++)); do
    for ((j=0; j<5; j++)); do
        ./main -i UNSORTED  < ../inputs/$i$j.in > ../outputs/u$i$j.out
        echo u$i$j
        ./main -i BINARY    < ../inputs/$i$j.in > ../outputs/b$i$j.out
        echo b$i$j
        ./main -i FIBONACCI < ../inputs/$i$j.in > ../outputs/f$i$j.out
        echo f$i$j
    done
done
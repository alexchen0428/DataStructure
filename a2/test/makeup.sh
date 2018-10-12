#!/bin/zsh
i=1
j=9
s=60000
for ((k=0; k<s; k++)); do
    echo $i $k | ./test< ../inputs/$j.in >> ../outs/123123$i.out
done
i=2
for ((k=0; k<s; k++)); do
    echo $i $k | ./test< ../inputs/$j.in >> ../outs/123123$i.out
done
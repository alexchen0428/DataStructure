#!/bin/zsh

for i in `seq 0 5`
do
    echo $i
    for j in `seq 0 7`
    do
        echo $i | ./a1_test < input$j >> same$i.out
        echo $j $?
    done
done 
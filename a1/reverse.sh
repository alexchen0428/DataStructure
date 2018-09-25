#!/bin/zsh

for i in `seq 3 5`
do
    echo $i
    for j in `seq 0 14`
    do
        echo $i | ./a1_test < input$j >> reverse$i.out
        echo $j $?
    done
done 
#!/bin/zsh

for i in `seq 0 2`
do
    echo $i
    for j in `seq 0 7`
    do
        echo $i | ./a1_test < input$j >> $i.out
        echo $j $?
    done
done 

for i in `seq 3 5`
do
    echo $i
    for j in `seq 8 14`
    do
        echo $i | ./a1_test < input$j >> $i.out
        echo $j $?
    done
done 
#rm -rf Testcase*
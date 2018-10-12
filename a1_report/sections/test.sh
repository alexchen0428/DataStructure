#!/bin/zsh

for ((i=0; i<3; i++)); do
    echo $i
    for ((j=0; j<8; j++)); do
        for ((k=0; k<5; k++)); do
            echo $i | ./a1_test < input$j$k >> $i$k.out
            echo $j $?
        done
    done
done 

for ((i=3; i<6; i++)); do
    echo $i
    for ((j=8; j<15; j++)); do
        for ((k=0; k<5; k++)); do
            echo $i | ./a1_test < input$j$k >> $i$k.out
            echo $j $?
        done
    done
done 
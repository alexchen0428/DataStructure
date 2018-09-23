#!/bin/zsh

for i in `seq 0 5`
do
    echo $i
    for j in `seq 0 14`
    do
        if [ $i -lt 3 -a $j -gt 4 ]
        then
            break
        fi
        echo $i | ./a1_test < input$j >> $i.out
        echo $j $?
    done
done 
#rm -rf Testcase*
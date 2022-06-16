#!/bin/bash

read -p "Enter file name: " filename
read -p "Enter starting line: " i
read -p "Enter ending line: " j

n=1
while read line; do
if [ $n -ge $i ] && [ $n -le $j ]; then
    echo "Line No. $n : $line"
    echo " "
fi
n=$((n+1))
done < $filename

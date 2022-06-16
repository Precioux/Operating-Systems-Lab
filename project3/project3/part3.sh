#!/bin/bash

RevSum(){   
  i=$(($x+0))
   s=0 
   reverse=0
   rem=0
   tmp=0
   ten=10
  while [ $x -ne 0 ]    
  do    
     rem=$(($x%$ten))
     s=$(($s + $rem))  
     tmp=$(($reverse*$ten))
     reverse=$(($tmp+$rem))   
     x=$(($x / $ten))
  done   
  echo "Reversed Number: $reverse"    
  echo "sum: $s"
  x=$(($i+0))
  
}

echo "Enter number : (0 to exit)"
x=-1
while [ $x -ne 0 ]
do
  read -p 'number => ' x
  RevSum
done

echo "Bye!"


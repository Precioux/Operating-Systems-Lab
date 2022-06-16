# !/bin/bash

echo "Enter two numbers:"
read -p "a= " a
read -p "b= " b

echo "which operation?"
echo "1- +"
echo "2- -"
echo "3- *"
echo "4- /"
read -p 'operation => ' op


case $op in
1)c=`echo $a+$b | bc`
;;
2)c=`echo $a-$b | bc`
;;
3)c=`echo $a*$b | bc`
;;
4)c=`echo $a/$b | bc`
;;
esac
echo "Result = $c"



# !/bin/bash

echo "Enter Two numbers : "
read a
read b

echo "which operation?"
echo "1- +"
echo "2- -"
echo "3- *"
echo "4- /"
read -p 'operation => ' op


case $op in
1)res=$(($a + $b))
;;
2)res=$(($a - $b))
;;
3)res=$(($a * $b))
;;
4)res=$(($a / $b))
;;
esac
echo "Result = $res"


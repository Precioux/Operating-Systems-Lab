#!/bin/bash

one(){
  for i in 1 2 3 4 5
do
   t=$(($i+0))
   while [ $t -ne 0 ]; do
     printf "%d " "$i"
     t=$(($t-1))
   done
   printf "\n"
done
}
 
spacer(){
    n=$(($space+0))
    while [ $n -ne 0 ];do
      printf " "
      n=$(($n-1))
    done
}
dotPrint()
{
   b=$(($i+0))
   while [ $b -ne 0 ];do
      printf ". "
      b=$(($b-1))
   done
}
up()
{
  for i in 1 2 3 4 5 6
do
   space=$((6-$i))
   spacer
   dotPrint
   spacer
   printf "\n"
done
}
down()
{
  for i in 6 5 4 3 2 1
do
   space=$((6-$i))
   spacer
   dotPrint
   spacer
   printf "\n"
done
}

two(){
   up
   down
}

three(){
 for j in 1 2 3 4 5 
do
     T=$(($j+0))
     S=$(($j-1))
     while [ $T -ne 0 ];do
       printf "|"
       if [ $S -ne 0 ];then
         printf " " 
         S=$(($S-1))
       fi
       T=$(($T-1))
     done
     printf "_"
     printf "\n"
done   
}

read -p "1,2 or 3?" choice

case $choice in
1)one
;;
2)two
;;
3)three
;;
esac



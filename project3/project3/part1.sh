#!/bin/bash
echo "Enter two numbers:"
read -p 'a:' a
read -p 'b:' b
 if [[ $a ]] && [ $a -eq $a 2>/dev/null ] && [[ $b ]] && [ $b -eq $b 2>/dev/null ]
  then
	let c=a+b
	echo "sum= $c"
	if [[ $a -ge $b ]] 
	then
  	  echo "$a is larger."
	else
  	  echo "$b is larger"
	fi
  else
     echo "$a or $b is not an integer or not defined"
  fi


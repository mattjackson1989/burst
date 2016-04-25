#!/bin/bash
#burst.sh
#Matt Jackson

#Options variable
array=( $@ )
len=${#array[@]}

if [ "$len" == 0 ]; then
  $((len=2))
fi

#Seperate the array
FILENAME=${array[$len - 1]}
OPTIONS=${array[@]:0:$len-1}

echo $FILENAME
echo $OPTIONS
#default lines are 500
DEFLINES=500

PATHNAME=$(echo $FILENAME | cut -f 1 -d '.')
split -l $DEFLINES -d --additional-suffix=.txt $FILENAME $PATHNAME  
echo $PATHNAME

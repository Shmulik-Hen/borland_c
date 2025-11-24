#! /bin/bash

files=$(find . -type f)

#echo $dirs
#exit 0

for file in $files; do
	f=$(basename $file)
	e=${f##*.}
	t=$(file $file)
#	echo $e $t
	echo $e
done


#!/bin/bash

files=$(git ls-files | grep -vE "doc|inc|txt")
#echo $files | tr ' ' '\n'

for file in $files; do
	grep -Hl [^[:print:][:blank:]] $file
done


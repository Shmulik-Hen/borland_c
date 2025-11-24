#! /bin/bash

dirs=$(find . -type d | tr '[:upper:]' '[:lower:]')

echo $dirs
#exit 0

for dir in $dirs; do
	pushd $dir
	mmv -rp '*' '#l1'
	popd
done


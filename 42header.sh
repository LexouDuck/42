#!/bin/bash
# set env variables USER and MAIL before calling this script
for f in $*
do
	echo "Processing $f..."
	vim -c ":d" -c ":Stdheader" -c ":wq" $f
done
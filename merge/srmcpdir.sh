#!/bin/bash

#usage: srmcpdir "srmdir" "dir"

for i in `ls $1`
do echo "cp $1/$i $2/$i"
   srmcp -2 -streams_num=1 srm://dcache-se-cms.desy.de:8443//$1/$i  file:///`pwd`/$2/$i
done

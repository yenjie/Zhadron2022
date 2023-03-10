#!/bin/bash

usage()
{
   echo "Usage: PrepareInput.sh Folder NumberPerExecute OutputBase [the rest...]"
}

if [[ "$1" == "-h" || "$1" == "--help" || "$#" -lt 3 ]]; then
   usage
   exit
fi

Directory=$1
shift

Number=$1
shift

OutputBase=$1
shift

Count=0
for i in `ls $Directory | Reformat $Number | sed "s/ /,/g" | sed "s/[,]*$//"`
do
   echo "./Execute --Input $i --Output $OutputBase/Result${Count}.root $@"
   Count=$(($Count + 1))
done





#!/bin/bash

echo Yay

CurrentFolder=$1
shift

ProjectBase=$1
shift

CMSSWBASE=$1
shift

Output=$1
shift

ID=$1
shift

cd $CMSSWBASE
eval `scramv1 runtime -sh`
cd - > /dev/null
export PATH=$ProjectBase/CommonCode/binary/:$PATH

echo "Running job with argument = '--Output Temp${ID}.root $@'"

$CurrentFolder/Execute --Output Temp${ID}.root $@
mv Temp${ID}.root $Output



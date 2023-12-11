#!/bin/bash

echo Yay

export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
source $VO_CMS_SW_DIR/cmsset_default.sh

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

cp $CurrentFolder/Execute .
./Execute --Output Temp${ID}.root $@
rm ./Execute

mv Temp${ID}.root $Output



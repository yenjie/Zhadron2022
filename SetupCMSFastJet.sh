pushd $CMSSW_BASE/
export `scramv1 tool info fastjet | grep FASTJET_BASE`
export FJConfig=$FASTJET_BASE/bin/fastjet-config
export FJCINCLUDE=`scramv1 tool info fastjet-contrib | grep INCLUDE | cut -d '=' -f 2`
export FJCLIB=`scramv1 tool info fastjet-contrib | grep "^LIB=" | cut -d '=' -f 2`
export FJCLIBDIR=`scramv1 tool info fastjet-contrib | grep LIBDIR | cut -d '=' -f 2`
popd

export FJExtra=`$FJConfig --cxxflags --libs`
export FJCExtra="-I$FJCINCLUDE -l$FJCLIB -L$FJCLIBDIR"

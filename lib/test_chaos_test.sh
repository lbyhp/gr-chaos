#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/edwin/Documents/GNURadio/gr-chaos/lib
export PATH=/home/edwin/Documents/GNURadio/gr-chaos/lib:$PATH
export LD_LIBRARY_PATH=/home/edwin/Documents/GNURadio/gr-chaos/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-chaos 

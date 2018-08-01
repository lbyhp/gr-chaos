#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/edwin/Documents/GNURadio/gr-chaos/python
export PATH=/home/edwin/Documents/GNURadio/gr-chaos/python:$PATH
export LD_LIBRARY_PATH=/home/edwin/Documents/GNURadio/gr-chaos/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/edwin/Documents/GNURadio/gr-chaos/swig:$PYTHONPATH
/usr/bin/python2 /home/edwin/Documents/GNURadio/gr-chaos/python/qa_DCSK_demod_cc.py 

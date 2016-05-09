#!/bin/sh
# simple PBS jobs info display
# add -n option to see what node jobs run on

qstat | grep $USER


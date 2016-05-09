#/bin/bash

rm */*.so
make clean

cd MoMA
make clean
make debug

cd ../
make debug
make release


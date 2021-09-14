#!/bin/bash -x
rm -rf ~/cliquest2/build
mkdir ~/cliquest2/build
cd ~/cliquest2/build
cmake -DCMAKE_BUILD_TYPE=Debug ~/cliquest2
make
cat ~/cliquest2/test/clisystemUT.inp | ~/cliquest2/build/test/clisystemUT
cat ~/cliquest2/test/clisceneUT.inp | ~/cliquest2/build/test/clisceneUT
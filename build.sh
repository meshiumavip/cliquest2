#!/bin/bash -x
rm -rf ~/cliquest2/build
mkdir ~/cliquest2/build
cd ~/cliquest2/build
cmake -DCMAKE_BUILD_TYPE=Debug ~/cliquest2
make
~/cliquest2/build/test/cliquest_test
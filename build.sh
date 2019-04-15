#!/usr/bin/env bash

rm ./pos_project
mkdir build

cd ./build
cmake ../
make

mv pos_project ../pos_project
cd ..
rm -rf build

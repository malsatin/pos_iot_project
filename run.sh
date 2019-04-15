#!/usr/bin/env bash

mkdir build

cd ./build
cmake ../
make

mv pos_project ../pos_project
cd ..
rm -rf build

echo
echo === RUN ===
echo

./pos_project

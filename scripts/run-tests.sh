#!/usr/bin/env bash

rm -rf ./bin
rm -rf ./build

mkdir -p build
cd build
cmake -G "Ninja" -DCMAKE_BUILD_TYPE="Release" ..
cmake --build .
cd ..
./bin/Release/semver-test

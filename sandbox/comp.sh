#!/bin/zsh

cd ../RVL
./comp.sh

cd ../sandbox
g++ -std=c++17 "src/game.cpp" -I"../RVL/src/" -I"../RVL/src/RVL/" -L"./" "RVL.dylib" -o "game228"

./game228

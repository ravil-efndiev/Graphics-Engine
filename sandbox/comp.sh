#!/bin/zsh

g++ -std=c++17 -L"./" "RVL.dylib" "src/game.cpp" -I"../RVL/src/" -o "game228"

./game228

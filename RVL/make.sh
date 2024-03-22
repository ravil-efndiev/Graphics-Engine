#!/bin/zsh

cd build
make
cp libRVL.a ../../sandbox/vendor
cp libRVL.a ../../RVLMapEditor/vendor
cp libRVL.a ../../RVLEditor/vendor
cp libRVL.a ../../topDownGame/vendor

cd ../
cp -r standart_assets ../sandbox/
cp -r standart_assets ../RVLEditor/
cp -r standart_assets ../RVLMapEditor/
cp -r standart_assets ../topDownGame/

#!/bin/zsh

g++ --verbose -dynamiclib -I"dependencies/include/" "dependencies/lib/libglfw3.a" "src/RVL.cpp" "src/RVL/RVLapp.cpp" "src/RVL/Window.cpp" -o "RVL.dylib" -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation -Wno-deprecated

cp RVL.dylib ../sandbox/

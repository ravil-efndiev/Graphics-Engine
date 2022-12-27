#!/bin/zsh

g++ -std=c++17 --verbose -dynamiclib -I"dependencies/include/" -I"src/" -I"src/RVL" "dependencies/lib/libglfw3.a" "src/verbose/glad/glad.c" "src/RVL/Core/RvlApp.cpp" "src/RVL/Core/Window.cpp" "src/RVL/Core/EventListener.cpp" "src/RVL/Events/WindowEvents.cpp" "src/RVL/Events/KeyEvents.cpp" "src/RVL/API/Input.cpp" -o "RVL.dylib" -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation -Wno-deprecated

cp RVL.dylib ../sandbox/

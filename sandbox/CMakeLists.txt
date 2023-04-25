cmake_minimum_required(VERSION 3.1)

project(sandbox)

add_executable(sandbox src/Game.cpp src/MainScene.cpp)

set_property(TARGET sandbox PROPERTY CXX_STANDARD 20)

target_link_libraries(sandbox "/Users/Belokan/RVL\ Engine/sandbox/vendor/libRVL.a" "/Users/Belokan/RVL Engine/RVL/vendor/lib/libglfw3.a")

target_include_directories(sandbox PRIVATE .)
target_include_directories(sandbox PRIVATE ../RVL/src/RVL)
target_include_directories(sandbox PRIVATE ../RVL/src)
target_include_directories(sandbox PRIVATE ../RVL/)

include(GNUInstallDirs)
set(CMAKE_CXX_FLAGS "-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation -Wno-deprecated")


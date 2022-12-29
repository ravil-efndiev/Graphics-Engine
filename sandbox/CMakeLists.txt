cmake_minimum_required(VERSION 3.1)

project(sandbox)

add_executable(sandbox src/game.cpp)

set_property(TARGET sandbox PROPERTY CXX_STANDARD 20)

target_link_libraries(sandbox "/Users/Belokan/RVL\ Engine/sandbox/vendor/libRVL.dylib")

target_include_directories(sandbox PRIVATE .)
target_include_directories(sandbox PRIVATE ../RVL/src/RVL)
target_include_directories(sandbox PRIVATE ../RVL/src)
target_include_directories(sandbox PRIVATE ../RVL/)

include(GNUInstallDirs)

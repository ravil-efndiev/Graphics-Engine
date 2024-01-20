cmake_minimum_required(VERSION 3.1)

project(sandbox)

add_executable(sandbox src/Main.cpp src/MainState.cpp)

set_property(TARGET sandbox PROPERTY CXX_STANDARD 20)

target_link_libraries(sandbox ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libRVL.a ${CMAKE_CURRENT_SOURCE_DIR}/../RVL/vendor/assimp/bin/libassimp.5.2.5.dylib ${CMAKE_CURRENT_SOURCE_DIR}/../RVL/vendor/lib/libglfw3.a)

set(CMAKE_BUILD_TYPE Release)

target_include_directories(sandbox PRIVATE .)
target_include_directories(sandbox PRIVATE ../RVL/src/RVL)
target_include_directories(sandbox PRIVATE ../RVL/src/RVL/API/)
target_include_directories(sandbox PRIVATE ../RVL/src/RVL/API/ECS)
target_include_directories(sandbox PRIVATE ../RVL/vendor/)
target_include_directories(sandbox PRIVATE ../RVL/vendor/include/)
target_include_directories(sandbox PRIVATE ../RVL/vendor/assimp/include/)
target_include_directories(sandbox PRIVATE ../RVL/vendor/yaml/include/)
target_include_directories(sandbox PRIVATE ../RVL/vendor/include/glm)
target_include_directories(sandbox PRIVATE ../RVL/vendor/imgui/)
target_include_directories(sandbox PRIVATE ../RVL/src)
target_include_directories(sandbox PRIVATE ../RVL/)

include(GNUInstallDirs)

set(CMAKE_CXX_FLAGS "-Wall -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation -Wno-unused -Wno-deprecated")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O4")

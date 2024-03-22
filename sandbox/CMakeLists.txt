cmake_minimum_required(VERSION 3.1)

project(sandbox)

add_executable(sandbox src/Main.cpp src/MainState.cpp)

set_property(TARGET sandbox PROPERTY CXX_STANDARD 20)

target_link_libraries(sandbox 
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libRVL.a 
    ${CMAKE_CURRENT_SOURCE_DIR}/../RVL/vendor/assimp/bin/libassimp.5.2.5.dylib
    ${CMAKE_CURRENT_SOURCE_DIR}/../RVL/vendor/lib/libglfw3.a
)

set(CMAKE_BUILD_TYPE Release)

target_include_directories(sandbox PRIVATE 
    .
    ../RVL/src/RVL
    ../RVL/src/RVL/API/
    ../RVL/src/RVL/API/ECS
    ../RVL/vendor/
    ../RVL/vendor/include/
    ../RVL/vendor/assimp/include/
    ../RVL/vendor/yaml/include/
    ../RVL/vendor/include/glm
    ../RVL/vendor/imgui/
    ../RVL/src
    ../RVL/
)

include(GNUInstallDirs)

set(CMAKE_CXX_FLAGS "-Wall -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation -Wno-unused -Wno-deprecated")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O4")

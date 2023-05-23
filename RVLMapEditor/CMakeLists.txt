cmake_minimum_required(VERSION 3.1)

project(rvm)

add_executable(rvm src/MapEditorApp.cpp src/MapScene.cpp)

set_property(TARGET rvm PROPERTY CXX_STANDARD 20)

target_link_libraries(rvm ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libRVL.a  ${CMAKE_CURRENT_SOURCE_DIR}/../RVL/vendor/lib/libglfw3.a)

set(CMAKE_BUILD_TYPE Release)

target_include_directories(rvm PRIVATE .)
target_include_directories(rvm PRIVATE ../RVL/src/RVL)
target_include_directories(rvm PRIVATE ../RVL/vendor/)
target_include_directories(rvm PRIVATE ../RVL/vendor/include/)
target_include_directories(rvm PRIVATE ../RVL/vendor/include/glm)
target_include_directories(rvm PRIVATE ../RVL/src)
target_include_directories(rvm PRIVATE ../RVL/)

include(GNUInstallDirs)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation -Wno-deprecated")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

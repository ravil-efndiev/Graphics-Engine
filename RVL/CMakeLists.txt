cmake_minimum_required(VERSION 3.1)

project(RVL)

add_library(RVL STATIC
    src/RVL/Core/RvlApp.cpp
    src/RVL/Core/Window.cpp
    src/RVL/Core/EventListener.cpp
    src/RVL/API/Input.cpp
    src/RVL/Events/KeyEvents.cpp
    src/RVL/Events/WindowEvents.cpp
    vendor/lib/glad/glad.c
)

set_property(TARGET RVL PROPERTY CXX_STANDARD 20)

target_include_directories(RVL PUBLIC .)
target_include_directories(RVL PUBLIC src)
target_include_directories(RVL PUBLIC src/RVL)
target_include_directories(RVL PRIVATE vendor/include)

include(GNUInstallDirs)

target_link_libraries(RVL /Users/Belokan/RVL\ Engine/RVL/vendor/lib/libglfw3.a)

set(CMAKE_CXX_FLAGS "-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation -Wno-deprecated")

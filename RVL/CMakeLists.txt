cmake_minimum_required(VERSION 3.1)

project(RVL)

add_library(RVL STATIC
    src/RVL/Core/App.cpp
    src/RVL/Core/State.cpp
    src/RVL/Core/Error.cpp
    src/RVL/Core/Types.cpp
    src/RVL/Core/Window.cpp
    src/RVL/Core/ImGuiController.cpp
    src/RVL/Core/Utils/Files.cpp
    src/RVL/Events/EventListener.cpp
    src/RVL/Events/KeyEvents.cpp
    src/RVL/Events/WindowEvents.cpp
    src/RVL/Events/CursorEvents.cpp
    src/RVL/Events/MouseEvents.cpp
    src/RVL/Rendering/OpenGL/GLContext.cpp
    src/RVL/Rendering/OpenGL/GLBuffer.cpp
    src/RVL/Rendering/OpenGL/GLTexture.cpp
    src/RVL/Rendering/OpenGL/GLVertexArray.cpp
    src/RVL/Rendering/OpenGL/GLShaderProgram.cpp
    src/RVL/Rendering/OpenGL/GLFrameBuffer.cpp
    src/RVL/Rendering/Renderer/Renderer.cpp
    src/RVL/Rendering/Renderer/SubTexture.cpp
    src/RVL/Rendering/Renderer/OrthographicCamera.cpp
    src/RVL/Rendering/Renderer/PerspectiveCamera.cpp
    src/RVL/Rendering/Renderer/Transform.cpp
    src/RVL/API/Input.cpp
    src/RVL/API/Time.cpp
    src/RVL/API/Random.cpp
    src/RVL/API/Math/Math.cpp
    src/RVL/API/Objects/UserOrthographicCamera.cpp
    src/RVL/API/Objects/TileSet.cpp
    src/RVL/API/ECS/Entity.cpp
    src/RVL/API/ECS/Scene.cpp
    src/RVL/API/ECS/Component.cpp
    src/RVL/API/ECS/Behaviour.cpp
    src/RVL/API/ECS/SpriteComponent.cpp
    src/RVL/API/ECS/TransformComponent.cpp
    src/RVL/API/ECS/TileMapComponent.cpp
    src/RVL/API/ECS/MovementComponent.cpp
    src/RVL/API/ECS/AnimationComponent.cpp

    # dependencies
    vendor/lib/glad/glad.c
    vendor/imgui/imgui.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/imgui_demo.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/lib/stb_image.cpp
)

set(CMAKE_BUILD_TYPE Release)

set_property(TARGET RVL PROPERTY CXX_STANDARD 20)

target_include_directories(RVL PUBLIC .)
target_include_directories(RVL PUBLIC src)
target_include_directories(RVL PUBLIC src/RVL)
target_include_directories(RVL PUBLIC src/RVL/Core)
target_include_directories(RVL PUBLIC vendor/)
target_include_directories(RVL PUBLIC vendor/imgui)
target_include_directories(RVL PRIVATE vendor/include)
target_include_directories(RVL PRIVATE vendor/include/glm)

include(GNUInstallDirs)

target_link_libraries(RVL /Users/Belokan/RVL\ Engine/RVL/vendor/lib/libglfw3.a)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation -Wno-deprecated -Wno-unused-command-line-argument")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

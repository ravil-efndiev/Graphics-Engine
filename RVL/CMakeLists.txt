cmake_minimum_required(VERSION 3.12)

project(RVL)

file(GLOB yamlFiles
    "vendor/yaml/src/*.h"
    "vendor/yaml/src/*.cpp"
)

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
    src/RVL/Rendering/Renderer/RenderCommand.cpp
    src/RVL/Rendering/Renderer/Renderer.cpp
    src/RVL/Rendering/Renderer/Renderer3D.cpp
    src/RVL/Rendering/Renderer/Mesh.cpp
    src/RVL/Rendering/Renderer/PostProcess.cpp
    src/RVL/Rendering/Renderer/SubTexture.cpp
    src/RVL/Rendering/Renderer/OrthographicCamera.cpp
    src/RVL/Rendering/Renderer/PerspectiveCamera.cpp
    src/RVL/Rendering/Renderer/ShaderLibrary.cpp
    src/RVL/Rendering/Renderer/ModelLoader.cpp
    src/RVL/Rendering/Renderer/StandartMeshes.cpp
    src/RVL/API/Input.cpp
    src/RVL/API/Time.cpp
    src/RVL/API/Random.cpp
    src/RVL/API/Math/Math.cpp
    src/RVL/API/Objects/UserCamera.cpp
    src/RVL/API/Objects/UserOrthographicCamera.cpp
    src/RVL/API/Objects/UserPerspectiveCamera.cpp
    src/RVL/API/Objects/SceneRenderer.cpp
    src/RVL/API/Objects/SceneSerializer.cpp
    src/RVL/API/Objects/TileSet.cpp
    src/RVL/API/ECS/Entity.cpp
    src/RVL/API/ECS/Scene.cpp
    src/RVL/API/ECS/Behaviour.cpp
    src/RVL/API/ECS/General/Transform.cpp
    src/RVL/API/ECS/2D/Sprite.cpp
    src/RVL/API/ECS/2D/TileMap.cpp
    src/RVL/API/ECS/2D/Movement2D.cpp
    src/RVL/API/ECS/2D/Animator2D.cpp
    src/RVL/API/ECS/3D/Model.cpp
    src/RVL/API/ECS/3D/DirectionalLight.cpp
    src/RVL/API/ECS/3D/PointLight.cpp
    src/RVL/API/ECS/3D/Material.cpp
    src/RVL/API/ECS/Systems/StandartSystems.cpp

    # dependencies
    vendor/lib/glad/glad.c
    vendor/imgui/imgui.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/imgui_demo.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/misc/cpp/imgui_stdlib.cpp
    vendor/lib/stb_image.cpp
    ${yamlFiles}
)

set(CMAKE_BUILD_TYPE Release)

set_property(TARGET RVL PROPERTY CXX_STANDARD 20)

target_include_directories(RVL PUBLIC .)
target_include_directories(RVL PUBLIC src)
target_include_directories(RVL PUBLIC src/RVL)
target_include_directories(RVL PUBLIC src/RVL/Core)
target_include_directories(RVL PUBLIC src/RVL/API/ECS)
target_include_directories(RVL PUBLIC src/RVL/API/)
target_include_directories(RVL PUBLIC vendor/)
target_include_directories(RVL PUBLIC vendor/assimp/include/)
target_include_directories(RVL PUBLIC vendor/imgui)
target_include_directories(RVL PUBLIC vendor/yaml/include/)
target_include_directories(RVL PRIVATE vendor/include)
target_include_directories(RVL PRIVATE vendor/include/glm)

include(GNUInstallDirs)

target_link_libraries(RVL ${CMAKE_CURRENT_SOURCE_DIR}/vendor/lib/libglfw3.a ${CMAKE_CURRENT_SOURCE_DIR}/vendor/assimp/lib/libassimp.a)

set(CMAKE_CXX_FLAGS "-Wall -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreFoundation -Wno-deprecated -Wno-unused-command-line-argument")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O4")

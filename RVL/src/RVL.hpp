#pragma once

/* ==========================================================================*  
||                                                                           ||   \
||        _______      ___        ______             _                       ||   |
||       |  __ \ \    / / |      |  ____|           (_)                      ||   |
||       | |__) \ \  / /| |      | |__   _ __   __ _ _ _ __   ___            ||   |
||       |  _  / \ \/ / | |      |  __| | '_ \ / _` | | '_ \ / _ \           ||   |
||       | | \ \  \  /  | |____  | |____| | | | (_| | | | | |  __/           ||   |
||       |_|  \_\  \/   |______| |______|_| |_|\__, |_|_| |_|\___|           ||   |
||                                            __/ |                          ||   |
||                                           |___/                           ||   |
||                                                                           ||   |
||                                                                           ||   |
||                                                                           ||   |
*============================================================================*    |
    \                                                                             |
     \----------------------------------------------------------------------------*/


#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RVL/Core/Core.hpp"
#include "RVL/Core/App.hpp"
#include "RVL/Core/State.hpp"
#include "RVL/Rendering/Renderer/Renderer.hpp"
#include "RVL/Rendering/Renderer/Renderer3D.hpp"
#include "RVL/Rendering/Renderer/SubTexture.hpp"
#include "RVL/Rendering/Renderer/PostProcess.hpp"
#include "RVL/Rendering/Renderer/ShaderLibrary.hpp"
#include "RVL/API/Objects/TileSet.hpp"
#include "RVL/API/Objects/UserPerspectiveCamera.hpp"
#include "RVL/API/Objects/UserOrthographicCamera.hpp"
#include "RVL/API/Objects/SceneRenderer.hpp"
#include "RVL/API/Objects/SceneSerializer.hpp"
#include "RVL/API/ECS/General/Transform.hpp"
#include "RVL/API/ECS/General/Identifier.hpp"
#include "RVL/API/ECS/2D/Animator2D.hpp"
#include "RVL/API/ECS/2D/Movement2D.hpp"
#include "RVL/API/ECS/2D/TileMap.hpp"
#include "RVL/API/ECS/2D/Sprite.hpp"
#include "RVL/API/ECS/3D/Model.hpp"
#include "RVL/API/ECS/3D/Material.hpp"
#include "RVL/API/ECS/3D/DirectionalLight.hpp"
#include "RVL/API/ECS/3D/PointLight.hpp"
#include "RVL/API/ECS/Behaviour.hpp"
#include "RVL/API/Input.hpp"
#include "RVL/API/Time.hpp"
#include "RVL/API/Random.hpp"
#include "RVL/API/Property.hpp"

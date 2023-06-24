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
||                  ** BRIEF DESCRIPTION AND COPYRIGHS **                    ||   |
||                                                                           ||   |
||                                                                           ||   |
*============================================================================*    |
    \                                                                             |
     \----------------------------------------------------------------------------*/


/*
        ** ALL NEEDED INFORMATION AND BIG DESCRIPTION **
*/
    

#include <imgui/imgui.h>
#include <glm/glm.hpp>

#include "RVL/Core/Core.hpp"
#include "RVL/Core/App.hpp"
#include "RVL/Core/State.hpp"
#include "RVL/Rendering/Renderer/Renderer.hpp"
#include "RVL/Rendering/Renderer/SubTexture.hpp"
#include "RVL/Rendering/Renderer/Transform.hpp"
#include <RVL/API/Objects/TileSet.hpp>
#include <RVL/API/Objects/UserPerspectiveCamera.hpp>
#include <RVL/API/Objects/UserOrthographicCamera.hpp>
#include <RVL/API/ECS/2D/AnimationComponent.hpp>
#include <RVL/API/ECS/2D/MovementComponent.hpp>
#include <RVL/API/ECS/2D/TransformComponent.hpp>
#include <RVL/API/ECS/2D/TileMapComponent.hpp>
#include <RVL/API/ECS/2D/SpriteComponent.hpp>
#include <RVL/API/ECS/Behaviour.hpp>
#include "RVL/API/Input.hpp"
#include "RVL/API/Time.hpp"
#include "RVL/API/Random.hpp"


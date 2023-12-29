#pragma once

#include <Core/Core.hpp>
#include <Core/Utils/Files.hpp>
#include <imgui/imgui_internal.h>

namespace Rvl
{
	void DragVec3(const std::string& label, glm::vec3* values, std::array<char, 3> elementNames = {'X', 'Y', 'Z'}, float columnWidth = 100.0f);

	void DragVec2(const std::string& label, glm::vec2* values, std::array<char, 2> elementNames = {'X', 'Y'}, float columnWidth = 100.0f);

	void DragFloat(const std::string& label, float* value, float columnWidth = 100.0f);
	
	void DragInt(const std::string& label, int* value, float columnWidth = 100.0f);

    std::string OpenFileDialogButton(const std::string& label, const char* extFilter, const char* startPath = "./");    

}


#include "GuiElements.hpp"
#include <nfd.h>

namespace Rvl
{

	void DragVec3(const std::string& label, glm::vec3* values, std::array<char, 3> elementNames, float columnWidth)
	{
        std::string labelDisp = Utils::SplitStr(label, '#').front();
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text("%s", labelDisp.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4.0f, 2.0f));
        ImGui::Text("%c", elementNames[0]);
		ImGui::SameLine();
		ImGui::DragFloat("##drag_x", &values->x, 0.1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

        ImGui::Text("%c", elementNames[1]);
		ImGui::SameLine();
		ImGui::DragFloat("##drag_y", &values->y, 0.1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

        ImGui::Text("%c", elementNames[2]);
		ImGui::SameLine();
		ImGui::DragFloat("##drag_z", &values->z, 0.1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);
		ImGui::PopID();
	}

    void DragVec2(const std::string& label, glm::vec2* values, std::array<char, 2> elementNames, float columnWidth)
    {
        std::string labelDisp = Utils::SplitStr(label, '#').front();
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text("%s", labelDisp.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4.0f, 2.0f));
        ImGui::Text("%c", elementNames[0]);
		ImGui::SameLine();
		ImGui::DragFloat("##drag_x", &values->x, 0.1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

        ImGui::Text("%c", elementNames[1]);
		ImGui::SameLine();
		ImGui::DragFloat("##drag_y", &values->y, 0.1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleVar();

		ImGui::Columns(1);
		ImGui::PopID();
    }

    void DragFloat(const std::string& label, float* value, float columnWidth)
    {
        std::string labelDisp = Utils::SplitStr(label, '#').front();

		ImGui::PushID(label.c_str());
		ImGui::Columns(2);
        
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text("%s", labelDisp.c_str());
		ImGui::NextColumn();
        
		ImGui::PushItemWidth(ImGui::CalcItemWidth() / 2.f);

        ImGui::Text(" ");
		ImGui::SameLine();
		ImGui::DragFloat("##float", value, 0.1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::Columns(1);
		ImGui::PopID();
    }

	void DragInt(const std::string& label, int* value, float columnWidth)
	{
		std::string labelDisp = Utils::SplitStr(label, '#').front();

		ImGui::PushID(label.c_str());
		ImGui::Columns(2);
        
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text("%s", labelDisp.c_str());
		ImGui::NextColumn();
        
		ImGui::PushItemWidth(ImGui::CalcItemWidth() / 2.f);

        ImGui::Text(" ");
		ImGui::SameLine();
		ImGui::DragInt("##int", value);
		ImGui::PopItemWidth();

		ImGui::Columns(1);
		ImGui::PopID();
	}

    std::string OpenFileDialogButton(const std::string& label, const char* extFilter, const char* startPath)
    {
        if (ImGui::Button(label.c_str()))
        {
            nfdchar_t* openPath = nullptr;
            nfdresult_t result = NFD_OpenDialog(extFilter, startPath, &openPath);

            if ( result == NFD_OKAY)
            {
                std::string str = openPath;
                free(openPath);
                return str;
            }
        }   
        return "";
    }

}

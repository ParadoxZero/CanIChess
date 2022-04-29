#include "api/imgui_utils.h"

#include <imgui.h>

namespace renderer::api {

    void imgui::CenteredText(std::string text)
    {
        auto windowWidth = ImGui::GetWindowSize().x;
        auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::Text(text.c_str());
    }

    void imgui::CenterWindowX(base::Vector2d parent_size)
    {

    }
}
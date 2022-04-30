#include "api/imgui_utils.h"

#include <imgui.h>

// namespace renderer::api {

void ImGui::CenteredText(const std::string text)
{
    auto windowWidth = ImGui::GetContentRegionAvail().x;
    auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::Text(text.c_str());
}

bool ImGui::CenteredButton(const std::string text)
{
    auto windowWidth = ImGui::GetContentRegionAvail().x;
    auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    return ImGui::Button(text.c_str());
}

void ImGui::CenterNextWindow(base::Vector2Du parent_size, base::Vector2Du windowSize)
{
    float next_start_position_x = (parent_size.x - windowSize.x) / 2.f;
    float next_start_position_y = (parent_size.y - windowSize.y) / 2.f;
    ImGui::SetNextWindowPos({next_start_position_x, next_start_position_y});
}
// }
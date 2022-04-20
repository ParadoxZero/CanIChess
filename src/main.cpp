// CanIChess.cpp : Defines the entry point for the application.
//

#include "renderer/api/window.h"

#include <imgui.h>
using namespace renderer::api;

using namespace std;

int main() 
{
    IWindow::WindowOptions options;
    auto window = renderer::api::IWindow::createWindow(options);
    window->initGUI();
    window->setImGuiLoop(
        [&window]
        {
            ImGui::SetNextWindowPos({ 50,50 });
            ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
            ImGui::Text("Can I Chess?");
            ImGui::Button("Start New Game");
            ImGui::Button("Leaderboard");
            if (ImGui::SmallButton("Exit"))
            {
                window->destroyWindow();
            }
            ImGui::End();
        }
    );
    window->startEventLoop();
    return 0;
}

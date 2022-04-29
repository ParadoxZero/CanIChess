// CanIChess.cpp : Defines the entry point for the application.
//

#include "renderer/api/window.h"

#include "imconfig.h"
#include <imgui.h>
using namespace renderer::api;

using namespace std;

void exit(IWindow *window)
{
    window->destroyWindow();
}
int main() 
{
    IWindow::WindowOptions options;
    auto window = renderer::api::IWindow::createWindow(options);
    window->initGUI();
    window->setImGuiLoop(
        [&window]
        {
            ImGui::SetNextWindowPos({ 50,50 });
            ImGui::SetNextWindowSize({ 250, 250 });
            ImGui::SetNextWindowFocus();
            ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
            ImGui::SetWindowFontScale(2);
            ImGui::Text("Can I Chess?");
            ImGui::SmallButton("Start New Game");
            ImGui::Button("Leaderboard");

            if (ImGui::Button("Exit"))
            {
                exit(window.get());
            }
            ImGui::End();
        }
    );
    window->startEventLoop();
    return 0;
}

// CanIChess.cpp : Defines the entry point for the application.
//

#include "renderer/api/window.h"

#include <imgui.h>
#include "renderer/api/imgui_utils.h"
#include "base/config.h"
#include "game/assets.h"

using namespace renderer::api;

using namespace std;

void exit(IWindow *window)
{
    window->destroyWindow();
}
int main(int argc, char *argv[])
{
    base::Config::getingleton()->addConfig(base::EXECUTABLE_PATH, argv[0]);

    IWindow::WindowOptions options;
    auto window = renderer::api::IWindow::createWindow(options);
    auto textureManager = window->getTextureManager();
    textureManager->addTexture(game::AssetId::WhiteTile, game::AssetPath[game::AssetId::WhiteTile]);
    auto sprite = window->createSprite(game::AssetId::WhiteTile);
    // sprite->setPosition({200, 300});
    sprite->setScale(10);
    window->initGUI();
    window->setImGuiLoop(
        [&window]
        {
            ImGui::CenterNextWindow(window->getSize(), {250, 250});
            ImGui::SetNextWindowSize({250, 250});
            ImGui::SetNextWindowFocus();
            ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
            ImGui::SetWindowFontScale(2);
            ImGui::CenteredText("Can I Chess?");
            ImGui::CenteredButton("Start New Game");
            ImGui::CenteredButton("Leaderboard");

            if (ImGui::CenteredButton("Exit"))
            {
                exit(window.get());
            }
            ImGui::End();
        });
    window->startEventLoop();
    return 0;
}

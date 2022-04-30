#ifndef __RENDERER_BACKEND_SFML__
#define __RENDERER_BACKEND_SFML__

#include "../../api/window.h"
#include "../../../base/cordinate.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "sfml_texture_manager.h"
#include "sfml_sprite.h"

#include <set>

namespace renderer::backend::sfml
{
    class Window : public renderer::api::IWindow
    {
    public:
        Window(base::Size2D position, base::Size2D size) : _window(sf::VideoMode(size.x, size.y), "Can I Chess?"),
                                                           _textureManager(new TextureManager()){};

        renderer::api::IWindow::RegistrationToken registerKeyboardEvent(renderer::api::KeyboardEventCallback callback) override;
        renderer::api::IWindow::RegistrationToken registerPointerEvent(renderer::api::PointerEventCallback callback) override;
        renderer::api::IWindow::RegistrationToken registerSystemEvents(renderer::api::SystemEventsCallback callback) override;
        bool updateWindowProps(WindowOptions &options) override;
        bool setImGuiLoop(std::function<void(void)> method) override;
        bool initGUI() override;
        bool startEventLoop() override;
        bool destroyWindow() override;

        base::Vector2Du getSize() override;
        base::Vector2Di getPosition() override;

        api::ISprite *createSprite(int textureId) override;
        api::ISprite *createSprite() override;
        bool removeSprite(api::ISprite *sprite) override;

        api::ITextureManager *getTextureManager() override;

        ~Window() override;

    private:
        std::vector<renderer::api::KeyboardEventCallback> _keyboardEventMethods;
        std::vector<renderer::api::PointerEventCallback> _pointerEventMethods;
        std::vector<renderer::api::SystemEventsCallback> _systemEventsCallbacks;
        std::set<std::shared_ptr<sf::Sprite>> _spriteSet;
        std::function<void(void)> _imGuiDrawer;

        sf::RenderWindow _window;
        std::unique_ptr<TextureManager> _textureManager;

        bool _isCloseWindow = false;

        bool _redirectEventToListeners(sf::Event event);
    };
}

#endif // !__RENDERER_BACKEND_SFML__

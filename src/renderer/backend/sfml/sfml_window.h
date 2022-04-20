#ifndef __RENDERER_BACKEND_SFML__
#define __RENDERER_BACKEND_SFML__

#include "../../api/window.h"
#include "../../../base/cordinate.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace renderer::backend::sfml
{
    class Window : public renderer::api::IWindow
    {
    public:

        Window(base::Size2D position, base::Size2D size) :
            _window(sf::VideoMode(size.x, size.y), "Can I Chess?") {};

        renderer::api::IWindow::RegistrationToken registerKeyboardEvent(renderer::api::KeyboardEventCallback callback) override;
        renderer::api::IWindow::RegistrationToken registerPointerEvent(renderer::api::PointerEventCallback callback) override;
        renderer::api::IWindow::RegistrationToken registerSystemEvents(renderer::api::SystemEventsCallback callback) override;
        bool updateWindowProps(WindowOptions& options) override;
        bool setImGuiLoop(std::function<void(void)> method) override;
        bool initGUI() override;
        bool startEventLoop() override;

        bool destroyWindow() override;

    private:
        std::vector<renderer::api::KeyboardEventCallback> _keyboardEventMethods;
        std::vector<renderer::api::PointerEventCallback> _pointerEventMethods;
        std::vector<renderer::api::SystemEventsCallback> _systemEventsCallbacks;
        std::function<void(void)> _imGuiDrawer;

        sf::RenderWindow _window;
        bool _isCloseWindow = false;

        bool _redirectEventToListeners(sf::Event event);
    };
}

#endif // !__RENDERER_BACKEND_SFML__

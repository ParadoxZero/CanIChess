#include "../../renderer_config.h"
#ifdef USE_SFML_BACKEND

#include "../../api/window.h"
#include "../../../base/cordinate.h"

#include <imgui-SFML.h>
#include <vector>

using namespace std;
using namespace renderer::api;

namespace renderer::backend::sfml {
    class Window : public IWindow
    {
    public:

        Window(base::Vector2d position, std::pair<uint32_t, uint32_t> size)

        RegistrationToken registerKeyboardEvent(KeyboardEventCallback callback) override;
        RegistrationToken registerPointerEvent(PointerEventCallback callback) override;
        RegistrationToken registerSystemEvents(SystemEventsCallback callback) override;
        bool updateWindowProps(WindowOptions& options) override;
        bool setImGuiLoop(std::function<void(void)> method) override;
        bool updateWindowProps(WindowOptions& options) override;
        bool initGUI() override;
        bool windowEventLoop() override;

        bool destroyWindow() override;

    private:
        vector<KeyboardEventCallback> _keyboardEventMethods;
        vector<PointerEventCallback> _pointerEventMethods;
        vector< SystemEventsCallback> _systemEventsCallbacks;
    };

    RegistrationToken Window::registerKeyboardEvent(KeyboardEventCallback callback)
    {
        return RegistrationToken();
    }
    RegistrationToken Window::registerPointerEvent(PointerEventCallback callback)
    {
        return RegistrationToken();
    }
    RegistrationToken Window::registerSystemEvents(SystemEventsCallback callback)
    {
        return RegistrationToken();
    }
    bool Window::updateWindowProps(WindowOptions& options)
    {
        return false;
    }
    bool Window::initGUI()
    {
        return false;
    }
    bool Window::windowEventLoop()
    {
        return false;
    }
    bool Window::setImGuiLoop(std::function<void(void)> method)
    {
        return false;
    }
    bool Window::destroyWindow()
    {
        return false;
    }
}

#endif // USE_SFML_BACKEND
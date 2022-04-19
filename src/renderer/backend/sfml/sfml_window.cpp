#include "../../renderer_config.h"
#ifdef USE_SFML_BACKEND

#include "../../api/window.h"

#include <vector>

using namespace std;
using namespace renderer::api;

namespace renderer::backend::sfml {
    class Window : public IWindow
    {
    public:

        RegistrationToken registerKeyboardEvent(KeyboardEventCallback callback) override;
        RegistrationToken registerPointerEvent(PointerEventCallback callback) override;
        bool updateWindowProps(WindowOptions& options) override;
        bool destroyWindow() override;

    private:
        vector<KeyboardEventCallback> _keyboardEventMethods;
        vector<PointerEventCallback> _pointerEventMethods;
    };

    RegistrationToken Window::registerKeyboardEvent(KeyboardEventCallback callback)
    {
        return RegistrationToken();
    }
    RegistrationToken Window::registerPointerEvent(PointerEventCallback callback)
    {
        return RegistrationToken();
    }
    bool Window::updateWindowProps(WindowOptions& options)
    {
        return false;
    }
    bool Window::destroyWindow()
    {
        return false;
    }
}

#endif // USE_SFML_BACKEND
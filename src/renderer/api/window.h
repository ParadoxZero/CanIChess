#ifndef __RENDERER_API_WINDOW__
#define __RENDERER_API_WINDOW__

#include "wrapper.h"
#include "event.h"

#include <memory>
#include <cstddef>

namespace renderer::api {
    class IWindow : IWrapper
    {
    public:
        struct WindowOptions
        {
            int x;
            int y;
        };

        typedef std::size_t RegistrationToken;

        static std::unique_ptr<IWindow> createWindow(WindowOptions& config);

        virtual RegistrationToken registerKeyboardEvent(KeyboardEventCallback callback) = 0;
        virtual RegistrationToken registerPointerEvent(PointerEventCallback callback) = 0;
        virtual RegistrationToken registerSystemEvents(SystemEventsCallback callback) = 0;
        virtual bool setImGuiLoop(std::function<void(void)> method) = 0;
        virtual bool updateWindowProps(WindowOptions& options) = 0;
        virtual bool initGUI() = 0;
        virtual bool startEventLoop() = 0;
        virtual bool destroyWindow() = 0;
    };
}

#endif // !__RENDERER_API_WINDOW__

#ifndef __RENDERER_API_WINDOW__
#define __RENDERER_API_WINDOW__

#include "wrapper.h"
#include "event.h"

#include <memory>
#include <cstddef>

#include "sprite.h"
#include "texure_manager.h"

namespace renderer::api
{

    class IWindow : IWrapper
    {
    public:
        struct WindowOptions
        {
            int size_x;
            int size_y;

            int contentSize_x;
            int contentSize_y;
        };

        typedef std::size_t RegistrationToken;

        static std::unique_ptr<IWindow> createWindow(WindowOptions &config);

        virtual RegistrationToken registerKeyboardEvent(KeyboardEventCallback callback) = 0;
        virtual RegistrationToken registerPointerEvent(PointerEventCallback callback) = 0;
        virtual RegistrationToken registerSystemEvents(SystemEventsCallback callback) = 0;

        virtual bool setImGuiLoop(std::function<void(void)> method) = 0;
        virtual bool updateWindowProps(WindowOptions &options) = 0;
        virtual bool initGUI() = 0;

        virtual bool startEventLoop() = 0;
        virtual bool destroyWindow() = 0;

        virtual base::Vector2Du getSize() = 0;
        virtual base::Vector2Di getPosition() = 0;

        virtual api::ISprite *createSprite(int textureId) = 0;
        virtual api::ISprite *createSprite() = 0;
        virtual bool removeSprite(api::ISprite *sprite) = 0;

        virtual ITextureManager *getTextureManager() = 0;

        virtual ~IWindow() = default;
    };
}

#endif // !__RENDERER_API_WINDOW__

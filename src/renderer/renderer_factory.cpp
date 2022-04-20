#include "api/window.h"
#include "renderer_config.h"

#ifdef USE_SFML_BACKEND

#include "backend/sfml/sfml_window.h"

#include "../base/cordinate.h"


namespace renderer::api {
    std::unique_ptr<IWindow> IWindow::createWindow(WindowOptions& config)
    {
        return std::unique_ptr<IWindow>(new renderer::backend::sfml::Window(base::Size2D { 0,0 }, base::Size2D { 640, 480 }));
    }

#endif // USE_SFML_BACKEND

}
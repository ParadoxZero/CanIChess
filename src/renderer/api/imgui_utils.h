#ifndef __RENDERER_API_IMGUI_UTILS__
#define __RENDERER_API_IMGUI_UTILS__

#include "window.h"

namespace renderer::api {

    namespace imgui {
        void CenteredText(std::string);
        void CenterWindowX(base::Vector2d parent_size);
    }
}
#endif // !__RENDERER_API_IMGUI_UTILS__

#ifndef __RENDERER_API_IMGUI_UTILS__
#define __RENDERER_API_IMGUI_UTILS__

#include "window.h"

// namespace renderer::api {

namespace ImGui
{
    void CenteredText(const std::string);
    bool CenteredButton(const std::string text);
    void CenterNextWindow(base::Vector2Du parent_size, base::Vector2Du windowSize);
}
// }
#endif // !__RENDERER_API_IMGUI_UTILS__

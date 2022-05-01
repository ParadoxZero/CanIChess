#ifndef __RENDERER_API_SPRITE__
#define __RENDERER_API_SPRITE__

#include <string>

#include "../../base/cordinate.h"

namespace renderer::api
{
    class ISprite
    {
    public:
        virtual bool setPosition(base::Vector2Di position) = 0;
        virtual bool move(base::Vector2Di delta) = 0;
        virtual bool rotate(float angle_degree) = 0;
        virtual bool setScale(float scale) = 0;
        virtual bool scale(float scale) = 0;

        virtual ~ISprite() = default;
    };
}

#endif // !__RENDERER_API_SPRITE__
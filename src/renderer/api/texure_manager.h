#ifndef __RENDERER_API_TEXURE_MANAGER__
#define __RENDERER_API_TEXURE_MANAGER__

#include <string>

namespace renderer::api
{
    typedef void *TexturePtr;

    class ITextureManager
    {
    public:
        virtual bool addTexture(int textureId, std::string texturePath) = 0;
        virtual TexturePtr getTexture(int textureId) = 0;

        virtual ~ITextureManager() = default;
    };
}

#endif
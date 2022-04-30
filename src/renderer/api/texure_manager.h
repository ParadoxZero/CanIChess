#ifndef __RENDERER_API_TEXURE_MANAGER__
#define __RENDERER_API_TEXURE_MANAGER__

#include <string>

namespace renderer::api
{
    typedef void *TextureID;

    class ITextureManager
    {
    public:
        virtual bool addTexture(std::string textureName, std::string texturePath) = 0;
        virtual TextureID getTexture(std::string name) = 0;
    };
}

#endif
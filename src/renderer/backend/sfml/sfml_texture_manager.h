#ifndef __RENDERER_BACKEND_SFML_TEXTURE_MANAGER__
#define __RENDERER_BACKEND_SFML_TEXTURE_MANAGER__

#include "../../api/texure_manager.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <filesystem>
#include <map>

namespace renderer::backend::sfml
{
    class TextureManager : public api::ITextureManager
    {
    public:
        TextureManager();
        bool addTexture(int textureId, std::string texturePath) override;
        api::TexturePtr getTexture(int textureId) override;

        sf::Texture *getTextureInternal(int textureId);
        std::shared_ptr<sf::Sprite> createSpriteInternal(int textureId);

    private:
        std::map<int, std::unique_ptr<sf::Texture>> _textureMap;
        std::filesystem::path _directoryPath;
    };
}

#endif
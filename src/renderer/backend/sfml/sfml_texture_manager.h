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
        bool addTexture(std::string textureName, std::string texturePath) override;
        api::TextureID getTexture(std::string name) override;

        sf::Texture *getTextureInternal(std::string name);
        std::shared_ptr<sf::Sprite> getSpriteInternal(std::string name);

    private:
        std::map<std::string, std::unique_ptr<sf::Texture>> _textureMap;
        std::filesystem::path _directoryPath;
    };
}

#endif
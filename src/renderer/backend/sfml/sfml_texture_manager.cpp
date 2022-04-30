#include "sfml_texture_manager.h"
#include <base/config.h>
#include <base/result.h>

namespace fs = std::filesystem;
namespace renderer::backend::sfml
{
    TextureManager::TextureManager()
    {
        std::string executablePath = base::Config::getingleton()->getConfig(base::EXECUTABLE_PATH);
        _directoryPath = fs::path(executablePath).remove_filename();
    }

    bool TextureManager::addTexture(int textureId, std::string texturePath)
    {
        std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

        fs::path absoluteTexturepath = _directoryPath / texturePath;
        RETURN_BOOL_IF_FALSE(texture->loadFromFile(absoluteTexturepath.c_str()));
        _textureMap[textureId] = std::move(texture);
        return true;
    }

    api::TexturePtr TextureManager::getTexture(int textureId)
    {
        sf::Texture *texture = _textureMap[textureId].get();
        return static_cast<void *>(texture);
    }

    sf::Texture *TextureManager::getTextureInternal(int textureId)
    {
        return _textureMap[textureId].get();
    }

    std::shared_ptr<sf::Sprite> TextureManager::createSpriteInternal(int textureId)
    {
        sf::Texture *texture = _textureMap[textureId].get();
        std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>();
        if (texture)
        {
            sprite->setTexture(*texture);
        }
        return sprite;
    }
}
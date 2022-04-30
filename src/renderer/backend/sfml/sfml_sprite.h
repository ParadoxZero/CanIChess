#ifndef __RENDERER_BACKEND_SFML_SPRITE__
#define __RENDERER_BACKEND_SFML_SPRITE__

#include "../../api/sprite.h"

#include <SFML/Graphics/Sprite.hpp>

#include <memory>
namespace renderer::backend::sfml
{
    class Sprite : public api::ISprite
    {
    public:
        Sprite(sf::Sprite sprite) : _sprite(new sf::Sprite(sprite)) {}
        Sprite(sf::Sprite *sprite) : _sprite(sprite) {}

        Sprite(const Sprite &old) = delete;
        Sprite(Sprite &&old) : _sprite(std::move(old._sprite)) {}

        bool setPosition(base::Vector2Di position) override;
        bool move(base::Vector2Di delta) override;
        bool rotate(float angle_degree) override;
        bool setScale(float scale) override;
        bool scale(float scale) override;

        sf::Sprite *getSfSprite();

    private:
        std::unique_ptr<sf::Sprite> _sprite;
    };
}

#endif
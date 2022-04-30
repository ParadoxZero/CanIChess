#include "sfml_sprite.h"

namespace renderer::backend::sfml
{
    sf::Vector2f toVector2f(base::Vector2Di vector)
    {
        float x = static_cast<float>(vector.x);
        float y = static_cast<float>(vector.y);
        return {x, y};
    }

    bool Sprite::setPosition(base::Vector2Di position)
    {
        _sprite->setPosition(toVector2f(position));
        return true;
    }

    bool Sprite::move(base::Vector2Di delta)
    {
        _sprite->move(toVector2f(delta));
        return true;
    }

    bool Sprite::rotate(float angle_degree)
    {
        _sprite->rotate(angle_degree);
        return true;
    }

    bool Sprite::setScale(float scale)
    {
        _sprite->setScale(scale, scale);
        return true;
    }

    bool Sprite::scale(float scale)
    {
        _sprite->scale(scale, scale);
        return true;
    }

    sf::Sprite *Sprite::getSfSprite()
    {
        return _sprite.get();
    }
}
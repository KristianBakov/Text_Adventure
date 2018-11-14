//
// Created by k2-bakov on 12/10/2018.
//

#include <Engine\Renderer.h>
#include "GameObject.h"

GameObject::~GameObject()
{
    freeSpriteComponent();
}

bool GameObject::addSpriteComponent(
        ASGE::Renderer* renderer, const std::string& texture_file_name)
{
    freeSpriteComponent();

    sprite_component = new SpriteComponent();
    if (sprite_component->loadSprite(renderer, texture_file_name))
    {
        return true;
    }

    freeSpriteComponent();
    return false;
}

void  GameObject::freeSpriteComponent()
{
    delete sprite_component;
    sprite_component = nullptr;
}


SpriteComponent* GameObject::spriteComponent()
{
    return sprite_component;
}

bool GameObject::isVisible()
{
    return visibility;
}

void GameObject::setVisible(bool vis_in)
{
    visibility = vis_in;
}

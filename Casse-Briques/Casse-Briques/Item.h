#pragma once
#include "MovableEntity.h"

class Item : public MovableEntity {
public:
	Item(int x, int y, sf::Texture& texture, sf::SoundBuffer* buffer = nullptr, float dx = 0.0f, float dy = 0.0f);

};


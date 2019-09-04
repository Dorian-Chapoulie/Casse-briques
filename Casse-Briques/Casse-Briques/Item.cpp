#include "Item.h"

Item::Item(int x, int y, sf::Texture& texture, sf::SoundBuffer* buffer, float dx, float dy)
	: MovableEntity(x, y, texture, buffer, dx, dy)
{}

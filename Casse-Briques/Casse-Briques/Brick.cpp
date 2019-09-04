#include "Brick.h"
#include "Ball.h"
#include "Bomb.h"

Brick::Brick(float x, float y, sf::Texture& texture, int health) 
	: Entity(x, y, texture), health(health)
{}

int Brick::getHealth()
{
	return this->health;
}


void Brick::onHit(Entity* e)
{
	if (static_cast<Ball*>(e) != nullptr) {
		this->health -= static_cast<Ball*>(e)->getDamage();

	}else if (static_cast<Bomb*>(e) != nullptr) {
		this->health -= static_cast<Bomb*>(e)->getDamage();
	}
}

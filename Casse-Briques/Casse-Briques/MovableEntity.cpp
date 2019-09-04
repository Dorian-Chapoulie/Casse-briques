#include "MovableEntity.h"

MovableEntity::MovableEntity(float x, float y, sf::Texture& texture, sf::SoundBuffer* buffer, float dx, float dy)
	: Entity(x, y, texture, buffer), dx(dx), dy(dy)
{}

void MovableEntity::move() const
{
	float speed = this->getSpeed();
	this->getSprite().move(dx * speed, dy * speed);
}


void MovableEntity::multiplySpeed(float vector)
{
	this->speed *= vector;
}

void MovableEntity::setSpeed(float newSpeed)
{
	this->speed = newSpeed;	
}

void MovableEntity::setDx(float newDx)
{
	this->dx = newDx;
}

void MovableEntity::setDy(float newDy)
{
	this->dy = newDy;
}

float MovableEntity::getSpeed() const
{
	return this->speed;
}

float MovableEntity::getDx() const
{
	return this->dx;
}

float MovableEntity::getDy() const
{
	return this->dy;
}

void MovableEntity::reset()
{
	this->speed = 2.0f;
	this->dx = 0;
}

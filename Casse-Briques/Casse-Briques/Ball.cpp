#include "Ball.h"
#include "Bar.h"
#include "utils.h"

Ball::Ball(float x, float y, sf::Texture& texture, sf::SoundBuffer* buffer, float dx, float dy) 
	: MovableEntity(x, y, texture, buffer, dx, dy)
{
	this->setDy(-1);
	this->setSpeed(3.2f);
}

int Ball::getDamage() const
{
	return this->damage;
}

void Ball::onHit(Entity* entity)
{	
	this->playSound();
	if (dynamic_cast<Bar*>(entity) != nullptr) {
		if (this->getDy() > 0) {
			this->setDy(this->getDy() * -1);
		}
		
		bool isNegatif = dynamic_cast<Bar*>(entity)->getDx() < 0;
		float newDx = 0.0f;


		if (isNegatif && this->getDx() > 0) {
			newDx = (float)utils::getRandom(7, 1) / 10 * -1;
		}
		else if (!isNegatif && this->getDx() > 0) {
			newDx = (float)utils::getRandom(10, 1) / 10 * 1;
		}
		else if (isNegatif && !this->getDx() > 0) {
			newDx = (float)utils::getRandom(10, 1) / 10 * - 1;
		}
		else {
			newDx = (float)utils::getRandom(7, 1) / 10 * -1;
		}
		
		this->setDx(newDx);
		
	}else {
		this->setDy(this->getDy() * -1);
	}	
}
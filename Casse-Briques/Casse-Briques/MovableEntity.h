#pragma once
#include "Entity.h"
class MovableEntity : public Entity
{
public:
	MovableEntity(float x, float y, sf::Texture& texture, sf::SoundBuffer* buffer = nullptr, float dx = 0.0f, float dy = 0.0f);

	virtual void move() const;
	virtual void reset();

	void multiplySpeed(float vector);
	void setSpeed(float newSpeed);
	void setDx(float newDx);
	void setDy(float newDy);

	float getSpeed() const;
	float getDx() const;
	float getDy() const;

private:
	float speed = 2.0f;
	float dx = 0;
	float dy = 0;
};


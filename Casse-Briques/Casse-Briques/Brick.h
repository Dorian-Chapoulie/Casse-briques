#pragma once
#include "Entity.h"


class Brick : public Entity {
public:
	Brick(float x, float y, sf::Texture& texture, int health = 100);
	int getHealth();

	void onHit(Entity* e) override;

private:
	int health = 200;
};


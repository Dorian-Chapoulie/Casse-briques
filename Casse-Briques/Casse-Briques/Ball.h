#pragma once
#include "Entity.h"
#include "MovableEntity.h"

class Ball : public MovableEntity {

public:
	Ball(float x, float y, sf::Texture& texture, sf::SoundBuffer* buffer = nullptr, float dx = 0, float dy = 1);

	int getDamage() const;

	void onHit(Entity* e) override;

private:
	int damage = 100;
};


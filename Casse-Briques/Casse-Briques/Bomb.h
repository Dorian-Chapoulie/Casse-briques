#pragma once
#include "Item.h"
#include "Bar.h"
#include "Brick.h"

class Bomb : public Item {
public:

	Bomb(int x, int y, sf::Texture& texture, Bar* bar, bool isPickedUp = false, sf::SoundBuffer* buffer = nullptr, sf::SoundBuffer* bufferExplosion = nullptr, float scale = 1.0f);
	Bomb(Bomb& bomb);

	void onHit(Entity* e) override;
	void move() const override;
	float getDamage() const;
	float getRadius() const;
	sf::Sound* getSoundExplosion() const;
	Bar* getBar() const;
	void throwItem();

private:
	Bar* bar;
	sf::Sound* soundExplosion;
	bool isPickedUp = false;
	float damage = 200.0f;
	float radius = 150.0f;
};


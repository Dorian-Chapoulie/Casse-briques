#pragma once
#include "Item.h"
class Speed : public Item {
public:
	Speed(int x, int y, sf::Texture& texture, sf::SoundBuffer* buffer = nullptr, float speed = 1.0f);
	void onHit(Entity* e) override;

private:
	float speedValue = 1.0f;
};


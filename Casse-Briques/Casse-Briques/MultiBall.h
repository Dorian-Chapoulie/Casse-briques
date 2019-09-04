#pragma once
#include "Item.h"
class MultiBall : public Item {

public:

	MultiBall(int x, int y, sf::Texture& texture, sf::SoundBuffer* buffer = nullptr);

	void onHit(Entity* e) override;

};


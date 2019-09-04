#pragma once
#include "Entity.h"
#include "Item.h"
#include "MovableEntity.h"

class Bar : public MovableEntity  {
public:
	Bar(sf::Texture& texture, sf::SoundBuffer* buffer = nullptr, float dx = 0, float dy = 0);

	void onHit(Entity* e) override;
	void reset() override;

	void replaceItems();
	void addItem(Item& item);
	int getItemThrowId() const;
	void decreaseItemThrowID();
	std::vector<Item*>& getItems() const;

private:
	std::vector<Item*> items;
	int itemThrowId = 0;
};


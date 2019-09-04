#include "Bar.h"
#include "Bomb.h"

Bar::Bar(sf::Texture& texture, sf::SoundBuffer* buffer, float dx, float dy)
	: MovableEntity(0, 0, texture, buffer, dx, dy) {
	this->setSpeed(5.0f);
}

void Bar::onHit(Entity* e)
{}

void Bar::reset()
{
	this->setSpeed(5.0f);
	this->items.clear();
}

void Bar::replaceItems()
{
	int sentItems = 0;
	for (auto item : items) {
		if (item->getPosition().y != this->getPosition().y) {
			sentItems++;
		}
	}

	if (sentItems > 0) {
		itemThrowId = items.size() - sentItems;
	}

	for (int i = 0; i < items.size(); i++) {
		if (items.at(i)->getPosition().y == this->getPosition().y) {
			items.at(i)->getSprite().setPosition(
				this->getPosition().x - ((this->sprite.getTexture()->getSize().x * this->sprite.getScale().x) / 2) * ((i - sentItems) + 1) + (items.at(i)->getSprite().getTexture()->getSize().x * items.at(i)->getSprite().getScale().x) / 2,
				this->getPosition().y
			);
		}
	}
}

void Bar::addItem(Item& item)
{
	item.getSprite().setPosition(
		this->getPosition().x - ((this->sprite.getTexture()->getSize().x * this->sprite.getScale().x) / 2) * (items.size() + 1),
		(int)item.getPosition().y
	);

	this->items.push_back(new Bomb(dynamic_cast<Bomb&>(item)));
	replaceItems();
}

int Bar::getItemThrowId() const
{
	return this->itemThrowId;
}

void Bar::decreaseItemThrowID()
{
	if (itemThrowId - 1 >= 0) {
		itemThrowId--;
	}
}

std::vector<Item*>& Bar::getItems() const
{
	return const_cast<std::vector<Item*>&>(this->items);
}

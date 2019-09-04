#include "Bomb.h"

Bomb::Bomb(int x, int y, sf::Texture& texture, Bar* bar, bool isPickedUp, sf::SoundBuffer* buffer, sf::SoundBuffer* bufferExplosion, float scale)
	: Item(x, y, texture, buffer, 0, 0.8), bar(bar), isPickedUp(isPickedUp)
{
	this->sprite.setScale(scale, scale);
	if (isPickedUp) {
		this->sprite.setPosition(
			bar->getPosition().x - (texture.getSize().x * scale) * (bar->getItems().size() + 1),
			bar->getPosition().y
		);
	}
	this->soundExplosion = new sf::Sound();
	this->soundExplosion->setBuffer(*bufferExplosion);
}
Bomb::Bomb(Bomb& bomb) 
	: Item((int)bomb.getPosition().x, (int)bomb.getPosition().y, (sf::Texture&)(*bomb.sprite.getTexture())), bar(bomb.getBar()), isPickedUp(true)
{	
	this->sprite.setPosition(
		bar->getPosition().x - (sprite.getTexture()->getSize().x * bomb.sprite.getScale().x) * (bar->getItems().size() + 1),
		bar->getPosition().y
	);
	this->sprite.setScale(bomb.sprite.getScale().x, bomb.sprite.getScale().y);
	this->soundExplosion = bomb.getSoundExplosion();
}

void Bomb::onHit(Entity* e) {
	if (!isPickedUp && dynamic_cast<Bar*>(e) != nullptr) {
		this->playSound();
		this->bar->addItem(*this);
	}
	else {
		this->soundExplosion->play();
	}
}

void Bomb::move() const {
	if (!this->isPickedUp) {
		float speed = this->getSpeed();
		this->getSprite().move(this->getDx() * speed, this->getDy() * speed);
	}
	else {
		this->getSprite().move(bar->getDx() * bar->getSpeed(), bar->getDy() * bar->getSpeed());
	}
}

float Bomb::getDamage() const
{
	return this->damage;
}

float Bomb::getRadius() const
{
	return this->radius;
}


sf::Sound* Bomb::getSoundExplosion() const
{
	return this->soundExplosion;
}

Bar* Bomb::getBar() const
{
	return this->bar;
}

void Bomb::throwItem()
{
	if (this->isPickedUp) {
		this->setDx(0);
		this->setDy(-1);
		this->sprite.setPosition(
			bar->getPosition().x + (bar->getSprite().getTexture()->getSize().x * bar->getSprite().getScale().x) / 2 
			- 
			(this->sprite.getTexture()->getSize().x * this->sprite.getScale().x) / 2,
			bar->getPosition().y - 10
		);
		this->isPickedUp = false;
	}	
}


#include "Entity.h"

Entity::Entity(int x, int y, sf::Texture& texture, sf::SoundBuffer* buffer)
{
	this->sprite.setTexture(texture);
	this->sprite.setPosition(x, y); 
	if (buffer != nullptr) {
		this->sound = new sf::Sound();
		this->sound->setBuffer(*buffer);
	}
}

sf::Vector2f Entity::getPosition() const {
	return this->sprite.getPosition();
}

sf::Sprite& Entity::getSprite() const
{
	return const_cast<sf::Sprite&>(sprite);
}

sf::SoundBuffer* Entity::getSoundBuffer() const
{
	return this->getSoundBuffer();
}

void Entity::playSound() const
{
	if (this->sound != nullptr && this->sound->getStatus() != sf::SoundSource::Playing)
		this->sound->play();
}

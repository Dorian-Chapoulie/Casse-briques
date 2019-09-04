#pragma once
#include "Vector2i.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Entity 
{

public:
	Entity(int x, int y, sf::Texture& texture, sf::SoundBuffer* buffer = nullptr);

	virtual void onHit(Entity* e = nullptr) = 0;
	virtual void playSound() const;

	sf::Vector2f getPosition() const;
	sf::Sprite& getSprite() const;
	sf::SoundBuffer* getSoundBuffer() const;

protected:
	sf::Sprite sprite;
	sf::Sound* sound = nullptr;
};

 
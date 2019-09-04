#include "MultiBall.h"
#include "ResourceManager.h"

MultiBall::MultiBall(int x, int y, sf::Texture& texture, sf::SoundBuffer* buffer)
	: Item(x, y, texture, buffer, 0, 0.8)
{}

void MultiBall::onHit(Entity* e) {
	this->playSound();
	ResourceManager::getInstance()->spawnBall();
}

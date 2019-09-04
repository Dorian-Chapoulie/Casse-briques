#include "Speed.h"
#include "Bar.h"
#include "utils.h"

Speed::Speed(int x, int y, sf::Texture& texture, sf::SoundBuffer* buffer, float speedValue)
	: Item(x, y, texture, buffer, 0, 0.8), speedValue(speedValue)
{}

void Speed::onHit(Entity * e) {
	if (static_cast<Bar*>(e) != nullptr) {
		static_cast<Bar*>(e)->multiplySpeed(this->speedValue);
		this->playSound();
	}
}


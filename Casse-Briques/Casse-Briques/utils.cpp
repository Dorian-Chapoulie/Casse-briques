#pragma once
#include <random>

namespace utils {
	int getRandom(int max, int min = 0) {
		std::random_device randomDevice;
		std::mt19937 generate(randomDevice());
		std::uniform_int_distribution<> createRandom(min, max);

		return createRandom(generate);
	}

	float get2Distance(sf::Vector2f a, sf::Vector2f b) {
		return sqrt(
			pow(b.x - a.x, 2) +
			pow(b.y - a.y, 2)
		);
	}
};
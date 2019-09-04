#pragma once
#include <random>

namespace utils {

	static int getRandom(int max, int min = 0) {
		std::random_device randomDevice;
		std::mt19937 generate(randomDevice());
		std::uniform_int_distribution<> createRandom(min, max);
		return createRandom(generate);
	}

};
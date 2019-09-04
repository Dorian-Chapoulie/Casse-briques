#pragma once
#include <thread>
#include "KeyboardManager.h"


class ContolersManager {

public:
	ContolersManager(int maxX, int maxY, Bar& bar);

	void checkKeyboard();

private:
	std::thread threadKeyboard;

	void listenKeyboard() const;

	KeyboardManager* keyboardManager;

	int maxX = 0;
	int maxY = 0;
};


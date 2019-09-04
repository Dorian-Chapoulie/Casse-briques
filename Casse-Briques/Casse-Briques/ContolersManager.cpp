#include "ContolersManager.h"

ContolersManager::ContolersManager(int maxX, int maxY, Bar& bar) : maxX(maxX), maxY(maxY) {
	this->keyboardManager = new KeyboardManager(bar);
}

void ContolersManager::listenKeyboard() const
{
	while (true) {
		this->keyboardManager->checkKeys();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	
}

void ContolersManager::checkKeyboard()
{
	this->threadKeyboard = std::thread(&ContolersManager::listenKeyboard, this);
}

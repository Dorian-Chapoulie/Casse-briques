#include "KeyboardManager.h"
#include "Game.h"
#include <windows.h>

KeyboardManager::KeyboardManager(Bar& bar) : bar(bar){
}


void KeyboardManager::checkKeys() const {
	if (GetAsyncKeyState(VK_LEFT) && this->bar.getPosition().x >= 0) {
		this->bar.setDx(-1);		
	}
	else if (GetAsyncKeyState(VK_RIGHT) && this->bar.getPosition().x <= Game::width - this->bar.getSprite().getTexture()->getSize().x * this->bar.getSprite().getScale().x) {
		this->bar.setDx(1);	
	}
	else if (GetAsyncKeyState(VK_SPACE) && this->bar.getItems().size() > 0) {
		dynamic_cast<Bomb*>(this->bar.getItems().at(bar.getItemThrowId()))->throwItem();		
		this->bar.replaceItems();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	else {
		this->bar.setDx(0);
	}
}

#include "Game.h"
#include "KeyboardManager.h"
#include "utils.cpp"
#include <Windows.h>

int Game::height = 0;
int Game::width = 0;
Game* Game::game = nullptr;

Game* Game::getInstance() {
	if (!Game::game) {
		Game::game = new Game();
	}
	return Game::game;
}

std::vector<sf::Sprite*>& Game::getBackgrounds() const
{
	return ResourceManager::getInstance()->getBackgrounds();
}

void Game::setSounds(sf::SoundBuffer& bufferWin, sf::SoundBuffer& bufferLoose)
{
	this->soundWin->setBuffer(bufferWin);
	this->soundLoose->setBuffer(bufferLoose);
}

void Game::init(unsigned int width, unsigned int height) {
	Game::width = width;
	Game::height = height;
}

Game::Game() {
	this->soundLoose = new sf::Sound();
	this->soundWin = new sf::Sound();
	this->setSounds(ResourceManager::getInstance()->getWinSoundBuffer(), ResourceManager::getInstance()->getLooseSoundBuffer());
	this->initLevel();
}

void Game::moveEnitys() const
{
	ResourceManager& ressourceManager = *ResourceManager::getInstance();
	Bar& bar = *ressourceManager.getBar();

	while (true) {
		if (!levelComplete && this->isPlaying) {
			for (auto movableEnty : ressourceManager.getMovableEntitys()) {
				movableEnty->move();
			}
			for (auto itemInventory : bar.getItems()) {
				itemInventory->move();
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Game::handleCollisions()
{
	ResourceManager& resourceManager = *ResourceManager::getInstance();
	Bar& bar = *ResourceManager::getInstance()->getBar();
	while (true) {
		for(auto ball : resourceManager.getBalls()) {
			if (ball->getSprite().getGlobalBounds().intersects(bar.getSprite().getGlobalBounds())) {
				ball->onHit(&bar);							
			}	
			for (auto brick : resourceManager.getBricks()) {			
				if (ball->getSprite().getGlobalBounds().intersects(brick->getSprite().getGlobalBounds())) {
					
					ball->onHit(brick);
					brick->onHit(ball);
					score++;
					
					this->handleBrick(brick);

				}
			}
			

			if (ball->getPosition().x <= 0) {
				ball->setDx(utils::getRandom((int)abs(ball->getDx()) || 1, 1));
				ball->playSound();
			}
			else if (ball->getPosition().x >= width - resourceManager.BALL_SIZE_WIDTH) {
				ball->setDx(-1 * utils::getRandom((int)ball->getDx() || 1, 1));
				ball->playSound();
			}

			if (ball->getPosition().y <= 0) {
				ball->setDy(1);
				ball->playSound();
			}
			else if (ball->getPosition().y >= height - resourceManager.BALL_SIZE_HEIGHT) {
				resourceManager.deleteEntity(ball);
				if (resourceManager.getBalls().size() <= 0) {	
					if (resourceManager.getBackgroundMusic().getStatus() == sf::Music::Playing) {
						resourceManager.getBackgroundMusic().pause();
					}
					this->soundLoose->play();				
					this->isPlaying = false;
					this->initRestart();
				}
			}
		}

		for (auto item : resourceManager.getItems()) {
			if (item->getSprite().getGlobalBounds().intersects(bar.getSprite().getGlobalBounds())) {
				item->onHit(&bar);
				score++;
				resourceManager.deleteEntity(item);
			}
		
		}
		
		for (auto itemInventory : bar.getItems()) {
			for (auto brick : resourceManager.getBricks()) {
				if (
					itemInventory->getSprite().getGlobalBounds().intersects(brick->getSprite().getGlobalBounds())
					|| itemInventory->getPosition().y <= itemInventory->getSprite().getTexture()->getSize().y * itemInventory->getSprite().getScale().y
					) {			
					for (auto brick2 : resourceManager.getBricks()) {
						if (
							utils::get2Distance(
								brick2->getPosition(),
								itemInventory->getPosition()
							) <= dynamic_cast<Bomb*>(itemInventory)->getRadius()) {
		
							brick2->onHit(itemInventory);							

							this->handleBrick(brick2);

							score++;
							resourceManager.deleteEntity(brick2);
						}
					}		

					itemInventory->onHit();

					if (std::find(bar.getItems().begin(), bar.getItems().end(), itemInventory) != bar.getItems().end() && bar.getItems().size() > 0) {
						resourceManager.createExplosion(dynamic_cast<Bomb*>(itemInventory));
						bar.getItems().erase(std::find(bar.getItems().begin(), bar.getItems().end(), itemInventory));
						bar.replaceItems();
						bar.decreaseItemThrowID();				
					}										
				}					
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	
}

void Game::animateTexts(std::string textString, std::string levelTextString)
{
	sf::Text* text = ResourceManager::getInstance()->getTexts().at(0);
	sf::Text* levelText = ResourceManager::getInstance()->getTexts().at(1);

	text->setString("");
	levelText->setString(levelTextString);

	std::vector<sf::Color> colors;
	colors.push_back(sf::Color::Black);
	colors.push_back(sf::Color::Red);
	colors.push_back(sf::Color::Blue);
	colors.push_back(sf::Color::Green);
	colors.push_back(sf::Color::Magenta);
	colors.push_back(sf::Color::Cyan);
	colors.push_back(sf::Color::Yellow);

	while (!isPlaying && !levelComplete) {		
		text->setFillColor(colors.at(utils::getRandom(colors.size() - 1)));
		text->setOutlineColor(colors.at(utils::getRandom(colors.size() - 1)));

		for (int i = 0; i <= this->level; i++) {
			levelText->setFillColor(sf::Color(
				colors.at(utils::getRandom(colors.size() - 1)).r,
				colors.at(utils::getRandom(colors.size() - 1)).g,
				colors.at(utils::getRandom(colors.size() - 1)).b,
				sf::Uint16(0)
			));
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			levelText->setFillColor(sf::Color(
				colors.at(utils::getRandom(colors.size() - 1)).r,
				colors.at(utils::getRandom(colors.size() - 1)).g,
				colors.at(utils::getRandom(colors.size() - 1)).b,
				sf::Uint16(255)
			));
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		for (int i = 0; i < textString.length(); i++) {
			text->setString(text->getString() + textString.at(i));
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		text->setString("");
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

bool Game::isGameStarted() const
{
	return this->isPlaying;
}

void Game::createBricks(unsigned int spaceBetween, float spriteScale) {

	std::vector<Brick*>* bricks = &ResourceManager::getInstance()->getBricks();
	unsigned int height = level;

	int spawnRenforcedBrickChance = RENFORCED_BRICK_CHANCE * 100 - level || 1;
	int y = 0;
	float x = 0.1;
	do {
		if (utils::getRandom(RENFORCED_BRICK_CHANCE * 100) == 1) {
			bricks->push_back(new Brick(
				x * (ResourceManager::BRICK_SIZE_WIDTH * spriteScale) + (x * spaceBetween),
				y * (ResourceManager::BRICK_SIZE_HEIGHT * spriteScale) + (y * spaceBetween),
				ResourceManager::getInstance()->getRandomRenforcedBrickTexture(),
				200
			));
		}
		else {
			bricks->push_back(new Brick(
				x * (ResourceManager::BRICK_SIZE_WIDTH * spriteScale) + (x * spaceBetween),
				y * (ResourceManager::BRICK_SIZE_HEIGHT * spriteScale) + (y * spaceBetween),
				ResourceManager::getInstance()->getRandomBrickTexture()
			));
		}
		bricks->back()->getSprite().setScale(0.2, 0.2);
	
		x++;
		if (x >= width / (ResourceManager::BRICK_SIZE_WIDTH * spriteScale) - 1){
			y++;
			x = 0.1;
		}
	} while (y != height);
}

void Game::handleBrick(Brick* brick)
{
	ResourceManager& resourceManager = *ResourceManager::getInstance();

	if (brick->getHealth() <= 0) {
		resourceManager.deleteEntity(brick);
		if (resourceManager.getBricks().size() <= 0) {
			this->soundWin->play();
			this->isPlaying = false;
			this->initNextLevel();
		}
		else {
			if (utils::getRandom(MAX_DROP_CHANCE * 100) >= 2) {
				resourceManager.spawnRandomItem(brick->getPosition());
			}
		}
	}
	else {
		resourceManager.changeRenforcedBrickTexture(*brick);
	}
}

void Game::initNextLevel()
{
	std::string text = "Complete !";
	std::string lvl = "Level: " + std::to_string(this->level);
	this->level++;
	threadTexts = new std::thread(&Game::animateTexts, this, text, lvl);

	while (this->soundWin->getStatus() == sf::Sound::Playing) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	this->levelComplete = true;
	threadTexts->join();
	
	ResourceManager::getInstance()->reinitEntitys();
	this->initLevel();
}

void Game::initLevel()
{
	this->levelComplete = false;
	this->createBricks(2, ResourceManager::getInstance()->BRICK_SCALE);
	std::string text = "Press space to Start";
	std::string lvl = "Level: " + std::to_string(this->level);
	threadTexts = new std::thread(&Game::animateTexts, this, text, lvl);
	sf::Color randomColor(utils::getRandom(255), utils::getRandom(255), utils::getRandom(255));
	this->getBackgrounds().at(0)->setColor(randomColor);
	this->getBackgrounds().at(1)->setColor(randomColor);
}

void Game::initRestart()
{
	std::string text = "Game Over";
	std::string lvl = "Score: " + std::to_string(score);
	this->level = 1;
	this->score = 0;

	threadTexts = new std::thread(&Game::animateTexts, this, text, lvl);

	while (this->soundLoose->getStatus() == sf::Sound::Playing) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	if (ResourceManager::getInstance()->getMenuMusic().getStatus() == sf::Music::Stopped) {
		ResourceManager::getInstance()->getMenuMusic().play();
	}

	ResourceManager::getInstance()->getBackgroundMusic().setPlayingOffset(sf::seconds(0));
	this->levelComplete = true;
	threadTexts->join();

	ResourceManager::getInstance()->reinitEntitys();
	this->initLevel();
}

std::vector<Brick*> Game::getBricks() const {
	return ResourceManager::getInstance()->getBricks();
}

std::vector<Ball*> Game::getBalls() const {
	return ResourceManager::getInstance()->getBalls();
}

std::vector<Item*> Game::getItems() const
{
	return ResourceManager::getInstance()->getItems();
}

std::vector<Item*> Game::getInventory() const
{
	return this->getBar()->getItems();
}

std::vector<Bomb*>& Game::getExpolosingBombs() const
{
	return  ResourceManager::getInstance()->getExpolosingBombs();
}

std::vector<sf::Text*> Game::handleStart()
{
	sf::Text* text = ResourceManager::getInstance()->getTexts().at(0);
	sf::Text* levelText = ResourceManager::getInstance()->getTexts().at(1);

	text->setOrigin(text->getGlobalBounds().width / 2, text->getGlobalBounds().height / 2);
	levelText->setOrigin(levelText->getGlobalBounds().width / 2, levelText->getGlobalBounds().height / 2);

	levelText->setPosition(width / 2, height / 2 - 50);
	text->setPosition(width / 2, height / 2);


	if (GetAsyncKeyState(VK_SPACE) && !isPlaying && !levelComplete) {
		if (threadMovableEntitys == nullptr) {
			threadMovableEntitys = new std::thread(&Game::moveEnitys, this);
		}
		if (threadCollision == nullptr) {
			threadCollision = new std::thread(&Game::handleCollisions, this);
		}
			
		this->isPlaying = true;	

		if (ResourceManager::getInstance()->getMenuMusic().getStatus() == sf::Music::Playing) {
			ResourceManager::getInstance()->getMenuMusic().stop();
		}
		if (ResourceManager::getInstance()->getBackgroundMusic().getStatus() != sf::Music::Playing) {
			ResourceManager::getInstance()->getBackgroundMusic().setLoop(true);
			ResourceManager::getInstance()->getBackgroundMusic().play();
		}
	}


	return ResourceManager::getInstance()->getTexts();
}

Bar* Game::getBar() const {
	return ResourceManager::getInstance()->getBar();
}



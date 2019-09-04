#pragma once
#include <vector>
#include <memory>
#include "ResourceManager.h"
#include "Brick.h"
#include "Ball.h"
#include "Bar.h"

class Game
{
public:
	static void init(unsigned int height, unsigned int width);
	static Game* getInstance();
	
	std::vector<sf::Sprite*>& getBackgrounds() const;
	std::vector<Brick*> getBricks() const;
	std::vector<Ball*> getBalls() const;
	std::vector<Item*> getItems() const;
	std::vector<Item*> getInventory() const;
	std::vector<Bomb*>& getExpolosingBombs() const;

	std::vector<sf::Text*> handleStart();

	bool isGameStarted() const;

	Bar* getBar() const;
	static int width;
	static int height;

private: 
	Game();
	static Game* game;

	void setSounds(sf::SoundBuffer& bufferWin, sf::SoundBuffer& bufferLoose);
	void createBricks(unsigned int spaceBetween = 0, float scale = 1.0f);
	void handleBrick(Brick* brick);
	void initNextLevel();
	void initLevel();
	void initRestart();

	std::thread* threadMovableEntitys;
	std::thread* threadCollision;
	std::thread* threadTexts;

	sf::Sound* soundWin = nullptr;
	sf::Sound* soundLoose = nullptr;

	void moveEnitys() const;
	void handleCollisions();
	void animateTexts(std::string text, std::string levelText);
	
	bool isPlaying = false;
	bool levelComplete = false;

	int level = 1;
	int score = 0;
	float MAX_DROP_CHANCE = 0.03;
	float RENFORCED_BRICK_CHANCE = 0.08;

};


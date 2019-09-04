#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "ContolersManager.h"

static constexpr int WIDTH = 800;
static constexpr int HEIGHT = 800;

using namespace std;
int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Casse Briques");

	Game::init(WIDTH, HEIGHT);
	Game* game = Game::getInstance();
	ContolersManager controlerManager(WIDTH, HEIGHT, *game->getBar());
	controlerManager.checkKeyboard();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		for (auto background : game->getBackgrounds()) {
			window.draw(*background);
		}
		for (auto brick : game->getBricks()) {
			window.draw(brick->getSprite());
		}
		for (auto ball : game->getBalls()) {
			window.draw(ball->getSprite());
		}
		for (auto item : game->getItems()) {
			window.draw(item->getSprite());
		}
		for (auto item : game->getInventory()) {
			window.draw(item->getSprite());
		}
		for (auto explosion : game->getExpolosingBombs()) {
			window.draw(explosion->getSprite());
		}
		window.draw(game->getBar()->getSprite());
	
		if (!game->isGameStarted()) {
			for (auto txt : game->handleStart()) {
				window.draw(*txt);
			}
		}
		
		
		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	return 0;
}
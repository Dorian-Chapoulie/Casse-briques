#pragma once
#include <vector>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Brick.h"
#include "Ball.h"
#include "Bar.h"
#include "Item.h"
#include "Speed.h"
#include "MultiBall.h"
#include "Bomb.h"

class ResourceManager
{
public:
	static ResourceManager* getInstance();

	static const int BRICK_SIZE_WIDTH = 384.0f;
	static const int BRICK_SIZE_HEIGHT = 128.0f;
	const float BRICK_SCALE = 0.2f;
	const float ITEM_SCALE = 0.15f;

	static const int BALL_SIZE_WIDTH = 22.0f;
	static const int BALL_SIZE_HEIGHT = 22.0f;

	static const int BAR_SIZE_WIDTH = 485;
	static const int BAR_SIZE_HEIGHT = 128;

	sf::Texture& getBrickTexture(int id) const;
	sf::Texture& getRandomBrickTexture() const;
	sf::Texture& getRandomRenforcedBrickTexture() const;
	sf::Texture& getBallTexture() const;
	sf::Texture& getBarTexture(int id) const;
	
	sf::SoundBuffer& getWinSoundBuffer() const;
	sf::SoundBuffer& getLooseSoundBuffer() const;

	sf::Music& getBackgroundMusic() const;
	sf::Music& getMenuMusic() const;

	std::vector<sf::Sprite*>& getBackgrounds() const;
	std::vector<MovableEntity*>& getMovableEntitys() const;
	std::vector<Brick*>& getBricks() const;
	std::vector<Ball*>& getBalls() const;
	std::vector<Item*>& getItems() const;
	std::vector<Bomb*>& getExpolosingBombs() const;
	std::vector<sf::Text*> getTexts() const;


	Bar* getBar() const;

	void deleteEntity(Entity* e);
	void spawnBall();
	void spawnRandomItem(sf::Vector2f position);
	void changeRenforcedBrickTexture(Brick& brick);
	void reinitEntitys();	
	void createExplosion(Bomb* bomb);

private:
	static ResourceManager* resourceManager;

	static const int ID_TEXTURE_BRICK_RENFORCED_1 = 1;
	static const int ID_TEXTURE_BRICK_RENFORCED_2 = 2;
	static const int ID_TEXTURE_BRICK_RENFORCED_3 = 3;
	static const int ID_TEXTURE_BRICK_RENFORCED_4 = 4;
	static const int ID_TEXTURE_BRICK_RENFORCED_5 = 5;
	static const int ID_TEXTURE_BRICK_RENFORCED_6 = 6;

	static const int ID_TEXTURE_BRICK_1 = 1;
	static const int ID_TEXTURE_BRICK_2 = 2;
	static const int ID_TEXTURE_BRICK_3 = 3;
	static const int ID_TEXTURE_BRICK_4 = 4;
	static const int ID_TEXTURE_BRICK_5 = 5;
	static const int ID_TEXTURE_BRICK_6 = 6;
	static const int ID_TEXTURE_BRICK_7 = 7;
	static const int ID_TEXTURE_BRICK_8 = 8;
	static const int ID_TEXTURE_BRICK_9 = 9;
	static const int ID_TEXTURE_BRICK_10 = 10;

	static const int ID_TEXTURE_BALL_1 = 1;
	static const int ID_TEXTURE_BAR_1 = 1;

	static const int ID_TEXTURE_ITEM_SPEED_POSITIF = 1;
	static const int ID_TEXTURE_ITEM_SPEED_NEGATIF = 2;
	static const int ID_TEXTURE_ITEM_MULTIBALL = 3;
	static const int ID_TEXTURE_ITEM_BOMB = 4;

	static const int  MAX_BRICKS_TEXTURES = 10;
	static const int  MAX_RENFORCED_BRICKS_TEXTURES = 6;
	static const int  MAX_BALL_TEXTURES = 1;
	static const int  MAX_BAR_TEXTURES = 6;

	static const int  ITEM_TYPES = 4;
	static const int  MAX_ITEMS_TEXTURES = 4;

	static const char* RES_PATH;
	static const char* BRICK_TEXTURE_NAME;
	static const char* RENFORCED_BRICK_TEXTURE_NAME;
	static const char* BALL_TEXTURE_NAME;
	static const char* BAR_TEXTURE_NAME;
	static const char* ITEMS_TEXTURE_NAME;
	static const char* EXPLOSION_NAME;

	static const char* BALL_BOUNCE_BUFFER;
	static const char* BONUS_BUFFER;
	static const char* MALUS_BUFFER;
	static const char* WIN_BUFFER;
	static const char* LOOSE_BUFFER;

	static const char* EXPLOSION_BUFFER;
	static const int EXPLOSION_TILES_NUMBER = 48;
	static const int EXPLOSION_TILES_WIDTH = 256;
	static const int EXPLOSION_TILES_HEIGHT = 256;

	static const char* FONT_PATH;

	static const char* BACKGROUND_MUSIC_PATH;
	static const char* MENU_MUSIC_PATH;

	static const char* BACKGROUND_NAME;
	const float BACKGROUND_SCALE_X = 1.0f;
	const float BACLGROUND_SCALE_Y = 1.15f;

	const float BAR_SCALE_WIDTH = 0.2f;
	const float BAR_SCALE_HEIGHT = 0.2f;

	static const int ANIMATION_DELAY = 100;
	static const int BACKGROUND_DELAY = 70;

	ResourceManager();
	void init();
	void resetEntitys();
	void animateAnimations();
	void animateBackground();
	void animateExplosion(Bomb* bomb);
	void spawnItem(Item* item);

	std::vector<sf::Texture> texturesBricks;
	std::vector<sf::Texture> texturesRenforcedBricks;
	std::vector<sf::Texture> texturesBall;
	std::vector<sf::Texture> texturesBar;
	std::vector<sf::Texture> texturesItems;
	std::vector<sf::Texture> texturesExplosion;

	std::vector<Brick*> bricks;
	std::vector<MovableEntity*> movableEntitys;
	std::vector<Item*> items;
	std::vector<Bomb*> explosingBombs;
	std::vector<Ball*> balls;
	std::vector<sf::Sprite*> backgrounds;
	std::vector<sf::Text*> texts;	

	sf::SoundBuffer soundBufferBall;
	sf::SoundBuffer soundBufferBonus;
	sf::SoundBuffer soundBufferMalus;
	sf::SoundBuffer soundBufferLoose;
	sf::SoundBuffer soundBufferWin;
	sf::SoundBuffer soundBufferExplosion;

	sf::Text text;
	sf::Text levelText;
	sf::Font font;

	sf::Texture textureBackground;

	sf::Music backgroundMusic;
	sf::Music menuMusic;

	Bar* bar = nullptr;

	std::thread threadAnimation;
	std::thread threadBackground;
	std::thread* bombAnimationThreads;
};


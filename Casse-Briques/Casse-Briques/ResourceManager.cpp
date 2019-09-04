#include "ResourceManager.h"
#include <string>
#include "utils.h"
#include "Game.h"


const char* ResourceManager::RES_PATH = "F:\\Repos\\Casse-briques\\res\\";

/*Textures*/
const char* ResourceManager::BRICK_TEXTURE_NAME = "-brick.png";
const char* ResourceManager::RENFORCED_BRICK_TEXTURE_NAME = "-renforced-brick.png";
const char* ResourceManager::BALL_TEXTURE_NAME = "-ball.png";
const char* ResourceManager::BAR_TEXTURE_NAME = "-bar.png";
const char* ResourceManager::ITEMS_TEXTURE_NAME = "-item.png";
const char* ResourceManager::BACKGROUND_NAME = "background.png";
const char* ResourceManager::EXPLOSION_NAME = "explosions.png";
/*Fonts*/
const char* ResourceManager::FONT_PATH = "8-bit-font.ttf";
/*Sounds*/
const char* ResourceManager::BALL_BOUNCE_BUFFER = "ball-bounce.wav";
const char* ResourceManager::BONUS_BUFFER = "bonus.wav";
const char* ResourceManager::MALUS_BUFFER = "malus.wav";
const char* ResourceManager::WIN_BUFFER = "win.wav";
const char* ResourceManager::LOOSE_BUFFER = "game-over.wav";
const char* ResourceManager::BACKGROUND_MUSIC_PATH = "background-music.wav";
const char* ResourceManager::MENU_MUSIC_PATH = "menu-music.wav";
const char* ResourceManager::EXPLOSION_BUFFER = "explosion.wav";

ResourceManager* ResourceManager::resourceManager = nullptr;


ResourceManager* ResourceManager::getInstance() {
	if (!ResourceManager::resourceManager) {
		ResourceManager::resourceManager = new ResourceManager();
	}
	return ResourceManager::resourceManager;
}

ResourceManager::ResourceManager() {	
	this->init();	
	threadAnimation = std::thread(&ResourceManager::animateAnimations, this);
	threadBackground = std::thread(&ResourceManager::animateBackground, this);
}

void ResourceManager::init() {
	this->textureBackground = sf::Texture();
	this->textureBackground.loadFromFile(std::string(RES_PATH) + std::string(BACKGROUND_NAME));
	this->textureBackground.generateMipmap();

	this->font.loadFromFile(std::string(RES_PATH) + std::string(FONT_PATH));
	this->text.setFont(this->font);
	this->levelText.setFont(this->font);
	this->texts.push_back(&this->text);
	this->texts.push_back(&this->levelText);

	this->backgrounds.push_back(new sf::Sprite());
	this->backgrounds.back()->setTexture(this->textureBackground);
	this->backgrounds.back()->setScale(BACKGROUND_SCALE_X, BACLGROUND_SCALE_Y);
	this->backgrounds.push_back(new sf::Sprite());
	this->backgrounds.back()->setTexture(this->textureBackground);
	this->backgrounds.back()->setScale(BACKGROUND_SCALE_X, BACLGROUND_SCALE_Y);

	this->texturesBricks.reserve(MAX_BRICKS_TEXTURES);
	this->texturesRenforcedBricks.reserve(MAX_RENFORCED_BRICKS_TEXTURES);
	this->texturesBall.reserve(MAX_BALL_TEXTURES);
	this->texturesBar.reserve(MAX_BAR_TEXTURES);
	this->texturesItems.reserve(MAX_ITEMS_TEXTURES);

	this->soundBufferBall.loadFromFile(std::string(RES_PATH) + std:: string(BALL_BOUNCE_BUFFER));
	this->soundBufferBonus.loadFromFile(std::string(RES_PATH) + std::string(BONUS_BUFFER));
	this->soundBufferMalus.loadFromFile(std::string(RES_PATH) + std::string(MALUS_BUFFER));
	this->soundBufferLoose.loadFromFile(std::string(RES_PATH) + std::string(LOOSE_BUFFER));
	this->soundBufferWin.loadFromFile(std::string(RES_PATH) + std::string(WIN_BUFFER));
	this->soundBufferExplosion.loadFromFile(std::string(RES_PATH) + std::string(EXPLOSION_BUFFER));

	this->backgroundMusic.openFromFile(RES_PATH + std::string(BACKGROUND_MUSIC_PATH));
	this->menuMusic.openFromFile(RES_PATH + std::string(MENU_MUSIC_PATH));
	menuMusic.setLoop(true);
	menuMusic.play();

	for (int i = 0; i < this->MAX_RENFORCED_BRICKS_TEXTURES; i++) {
		this->texturesRenforcedBricks.push_back(sf::Texture());
		this->texturesRenforcedBricks.at(i).loadFromFile(std::string(RES_PATH) + std::to_string(i + 1) + std::string(RENFORCED_BRICK_TEXTURE_NAME));
	}

	for (int i = 0; i < this->MAX_BRICKS_TEXTURES; i++) {
		this->texturesBricks.push_back(sf::Texture());
		this->texturesBricks.at(i).loadFromFile(std::string(RES_PATH) + std::to_string(i + 1) + std::string(BRICK_TEXTURE_NAME));
	}
	
	for (int i = 0; i < this->MAX_BALL_TEXTURES; i++) {
		this->texturesBall.push_back(sf::Texture());
		this->texturesBall.at(i).loadFromFile(std::string(RES_PATH) + std::to_string(i + 1) + std::string(BALL_TEXTURE_NAME));
	}

	for (int i = 0; i < this->MAX_BAR_TEXTURES; i++) {
		this->texturesBar.push_back(sf::Texture());
		this->texturesBar.at(i).loadFromFile(std::string(RES_PATH) + std::to_string(i + 1) + std::string(BAR_TEXTURE_NAME));
	}

	for (int i = 0; i < this->MAX_ITEMS_TEXTURES; i++) {
		this->texturesItems.push_back(sf::Texture());
		this->texturesItems.at(i).loadFromFile(std::string(RES_PATH) + std::to_string(i + 1) + std::string(ITEMS_TEXTURE_NAME));		
	}

	int x = 0, y = 0;
	for (int i = 0; i < this->EXPLOSION_TILES_NUMBER; i++) {
		this->texturesExplosion.push_back(sf::Texture());
		this->texturesExplosion.at(i).loadFromFile(
			std::string(RES_PATH) + std::string(EXPLOSION_NAME), 
			sf::IntRect(
				x * EXPLOSION_TILES_WIDTH + 45, 
				y * EXPLOSION_TILES_HEIGHT + 30,
				EXPLOSION_TILES_WIDTH,
				EXPLOSION_TILES_HEIGHT
			)
		);

		x++;
		if (x == 8) {
			x = 0;
			y++;
		}
	}

	this->reinitEntitys();
}

void ResourceManager::reinitEntitys()
{
	this->resetEntitys();

	this->balls.push_back(new Ball(400, 700, this->texturesBall.at(0), &this->soundBufferBall));
	this->balls.back()->getSprite().setPosition(Game::width / 2 - this->balls.back()->getSprite().getTexture()->getSize().x / 2, 700);

	if (!this->bar) {
		this->bar = new Bar(this->texturesBar.at(0));
		this->bar->getSprite().setPosition(Game::width / 2 - this->bar->getSprite().getTexture()->getSize().x * BAR_SCALE_WIDTH / 2, 760);
		this->bar->getSprite().setScale(BAR_SCALE_WIDTH, BAR_SCALE_WIDTH);
	}
	else {
		this->bar->reset();
		this->bar->getSprite().setPosition(Game::width / 2 - this->bar->getSprite().getTexture()->getSize().x * BAR_SCALE_WIDTH / 2, 760);
	}

	this->movableEntitys.push_back(balls.at(0));
	this->movableEntitys.push_back(this->bar);
}

void ResourceManager::createExplosion(Bomb* bomb)
{
	this->bombAnimationThreads = new std::thread(&ResourceManager::animateExplosion, this, bomb);
}

void ResourceManager::resetEntitys()
{
	this->balls.clear();
	this->movableEntitys.clear();
	this->items.clear();
	this->explosingBombs.clear();
	this->bricks.clear();
}

void ResourceManager::animateBackground() {
	int backgroundDx = -1;
	float backgroundTextureSize = this->backgrounds.at(0)->getTexture()->getSize().x;
	this->backgrounds.at(1)->setPosition(backgroundTextureSize, 0);

	while (true)
	{

		this->backgrounds.at(0)->move(backgroundDx, 0);
		this->backgrounds.at(1)->move(backgroundDx, 0);

		int backgroundLength = backgroundTextureSize + this->backgrounds.at(0)->getPosition().x;
		int backgroundLength2 = backgroundTextureSize + this->backgrounds.at(1)->getPosition().x;

		if (backgroundLength <= 0) {
			this->backgrounds.at(0)->setPosition(this->backgrounds.at(1)->getPosition().x + backgroundTextureSize, 0);
		}
		if (backgroundLength2 <= 0) {
			this->backgrounds.at(1)->setPosition(this->backgrounds.at(0)->getPosition().x + backgroundTextureSize, 0);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(BACKGROUND_DELAY));
	}
}
void ResourceManager::animateExplosion(Bomb* bomb)
{
	this->explosingBombs.push_back(new Bomb(*bomb));
	int bombIndex = this->explosingBombs.size() - 1;
	
	this->explosingBombs.at(bombIndex)->getSprite().setScale(0.35, 0.35);
	this->explosingBombs.at(bombIndex)->getSprite().setPosition(
		bomb->getPosition().x - (EXPLOSION_TILES_WIDTH * 0.35) / 2,
		bomb->getPosition().y - (EXPLOSION_TILES_HEIGHT * 0.35) / 2
	);

	for (int i = 0; i < EXPLOSION_TILES_NUMBER; i++) {
		this->explosingBombs.at(bombIndex)->getSprite().setTexture(this->texturesExplosion.at(i));
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}


}
void ResourceManager::animateAnimations()
{
	int textureId = 0;
	while (true)
	{
		this->bar->getSprite().setTexture(this->getBarTexture(textureId));
		textureId++;
		if (textureId >= MAX_BAR_TEXTURES) {
			textureId = 0;
		}
	
		std::this_thread::sleep_for(std::chrono::milliseconds(ANIMATION_DELAY));
			
	}
	
}


sf::Texture& ResourceManager::getBrickTexture(int id) const {
	if (id < 0 || id >= texturesBricks.size()) {
		throw new const char*("Error: bad ID");
	}
	return const_cast<sf::Texture&>(this->texturesBricks.at(id));
}

sf::Texture& ResourceManager::getRandomBrickTexture() const {
	return const_cast<sf::Texture&>(this->texturesBricks.at( utils::getRandom(MAX_BRICKS_TEXTURES - 1, 1) )); //-1 => vector start at 0
}

sf::Texture& ResourceManager::getRandomRenforcedBrickTexture() const
{
	return const_cast<sf::Texture&>(this->texturesRenforcedBricks.at(utils::getRandom(MAX_RENFORCED_BRICKS_TEXTURES - 1, 1))); //-1 => vector start at 0
}

sf::Texture& ResourceManager::getBallTexture() const
{
	return const_cast<sf::Texture&>(this->texturesBall.at(0));
}

sf::Texture& ResourceManager::getBarTexture(int id) const
{
	return const_cast<sf::Texture&>(this->texturesBar.at(id));
}

sf::SoundBuffer& ResourceManager::getWinSoundBuffer() const
{
	return const_cast<sf::SoundBuffer&>(this->soundBufferWin);
}

sf::SoundBuffer& ResourceManager::getLooseSoundBuffer() const
{
	return const_cast<sf::SoundBuffer&>(this->soundBufferLoose);
}

sf::Music& ResourceManager::getBackgroundMusic() const
{
	return const_cast<sf::Music&>(this->backgroundMusic);
}

sf::Music& ResourceManager::getMenuMusic() const
{
	return const_cast<sf::Music&>(this->menuMusic);
}

std::vector<sf::Sprite*>& ResourceManager::getBackgrounds() const
{
	return const_cast<std::vector<sf::Sprite*>&>(this->backgrounds);
}

std::vector<MovableEntity*>& ResourceManager::getMovableEntitys() const
{
	return const_cast<std::vector<MovableEntity*>&>(this->movableEntitys);
}

std::vector<Brick*>& ResourceManager::getBricks() const
{
	return const_cast<std::vector<Brick*>&>(this->bricks);
}

std::vector<Ball*>& ResourceManager::getBalls() const
{
	return const_cast<std::vector<Ball*>&>(this->balls);
}

std::vector<Item*>& ResourceManager::getItems() const
{
	return const_cast<std::vector<Item*>&>(this->items);
}

std::vector<Bomb*>& ResourceManager::getExpolosingBombs() const
{
	return const_cast<std::vector<Bomb*>&>(this->explosingBombs);
}


Bar* ResourceManager::getBar() const
{
	return this->bar;
}

void ResourceManager::deleteEntity(Entity* e)
{

	if (std::find(this->movableEntitys.begin(), this->movableEntitys.end(), e) != this->movableEntitys.end()) {
		this->movableEntitys.erase(std::find(this->movableEntitys.begin(), this->movableEntitys.end(), e));

	}
	if (std::find(this->bricks.begin(), this->bricks.end(), e) != this->bricks.end()) {
		this->bricks.erase(std::find(this->bricks.begin(), this->bricks.end(), e));

	}
	if (std::find(this->balls.begin(), this->balls.end(), e) != this->balls.end()) {
		this->balls.erase(std::find(this->balls.begin(), this->balls.end(), e));
	}
	if (std::find(this->items.begin(), this->items.end(), e) != this->items.end()) {
		this->items.erase(std::find(this->items.begin(), this->items.end(), e));
	}
	
}


void ResourceManager::spawnItem(Item* item)
{
	this->items.push_back(item);
	this->items.back()->getSprite().setScale(ITEM_SCALE, ITEM_SCALE);
	this->movableEntitys.push_back(this->items.back());
}

void ResourceManager::spawnBall()
{
	this->balls.push_back(new Ball(
		this->bar->getPosition().x + (this->bar->getSprite().getTexture()->getSize().x * BAR_SCALE_WIDTH) / 2,
		this->bar->getPosition().y - 10, this->texturesBall.at(0),
		&this->soundBufferBall
	));
	this->balls.back()->getSprite().setColor(sf::Color(utils::getRandom(255), utils::getRandom(255), utils::getRandom(255)));
	this->balls.back()->setDx(1 * (utils::getRandom(7,1) > 5 ? 1 : -1));
	this->movableEntitys.push_back(this->balls.back());
}

void ResourceManager::spawnRandomItem(sf::Vector2f position)
{
	switch (utils::getRandom(ITEM_TYPES, 1)) {
		case 1:
			this->spawnItem(new Speed(position.x, position.y, texturesItems.at(ID_TEXTURE_ITEM_SPEED_NEGATIF - 1), &this->soundBufferMalus, 0.7));
		break;
		case 2:
			this->spawnItem(new Speed(position.x, position.y, texturesItems.at(ID_TEXTURE_ITEM_SPEED_POSITIF - 1), &this->soundBufferBonus, 1.2));
		break;
		case 3:
			this->spawnItem(new MultiBall(position.x, position.y, texturesItems.at(ID_TEXTURE_ITEM_MULTIBALL - 1), &this->soundBufferBonus));
		break;
		case 4:
			this->spawnItem(new Bomb(
				position.x,
				position.y,
				texturesItems.at(ID_TEXTURE_ITEM_BOMB - 1),
				this->bar,
				false,
				&this->soundBufferBonus,
				&this->soundBufferExplosion,
				0.1
			));
		break;
	};
}

void ResourceManager::changeRenforcedBrickTexture(Brick& renforcedBrick)
{
	for (int i = 0; i < MAX_RENFORCED_BRICKS_TEXTURES; i++) {
		if (renforcedBrick.getSprite().getTexture() == &this->texturesRenforcedBricks.at(i)) {
			renforcedBrick.getSprite().setTexture(this->texturesBricks.at(i));
		}
	}
}

std::vector<sf::Text*> ResourceManager::getTexts() const
{
	return this->texts;
}


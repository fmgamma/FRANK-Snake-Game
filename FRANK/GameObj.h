#pragma once


#include "SFML/Graphics.hpp"
#include "Utils.h"

struct Game;
/*
A game object is anything represented by a sprite that exists in the game world
Rocks, the player's ship, enemy ships, bullets - all game objects with sprites, hela
*/
struct GameObj
{
	sf::Sprite spr;					//main image
	enum class ObjectT { SHead, SBody, Apple};	//what is this object instance?
	ObjectT type = ObjectT::SHead;	//what type am I?
	bool active = false;			//should we be updating and rendering this one?
	Game *pGame = nullptr;			//keep a pointer (a handle) to my owner the game object
	sf::Vector2i gridPos = {};
	sf::Vector2i oldPos = {};
	GameObj* prevObj = nullptr;
	int xVel = 0;
	int yVel = 0;
	int health = 1;
	
	void Init(sf::RenderWindow& window, sf::Texture& tex, ObjectT type_, Game& game);

	//APPLE
	void InitApple();

	void UpdateApple();

	//SNAKE
	void InitSHead();

	void InitSBody();

	void UpdateSBody();

	
	//BG/GRID/TILES
	void InitBG(sf::RenderWindow& window, sf::Texture& tex);
	
	void IncGridPosition(int xVelocity, int yVelocity);

	void SetGridPosition(sf::Vector2i pos);

	void SetGridPosition(int xVelocity, int yVelocity);

	//GENERAL
	void Update(sf::RenderWindow& window, float elapsed);
	
	void Render(sf::RenderWindow& window, float elapsed);
	
	void PlayerControl(const sf::Vector2u& screenSz, float elapsed);

};


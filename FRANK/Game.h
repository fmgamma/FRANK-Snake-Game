#pragma once

#include "SFML/Graphics.hpp"
#include "Utils.h"
#include "GameObj.h"
#include <vector>
/*
A box to put Games Constants in.
These are special numbers with important meanings (screen width,
ascii code for the escape key, number of lives a player starts with,
the name of the title screen music track, etc.
*/
namespace GC
{
	//game play related constants to tweak
	const Dim2Di SCREEN_RES{ 600,600 };
	const float REFRESH_SPEED = 1.0f;
	const int GRID_HEIGHT{ 12 };
	const int GRID_WIDTH{ 12 };
	const float TEX_HEIGHT{384};
	const float TEX_WIDTH{384};
	const float MOVE_DELAY{ 0.5f };
}


//GAME STRUCT
struct Game
{
	sf::RenderWindow* pWindow = nullptr;
	//textures we are going to need, load them once only
	sf::Texture spriteSheet;
	sf::Sprite grid[GC::GRID_WIDTH][GC::GRID_HEIGHT];
	std::vector<GameObj> objects;	//anything moving around
	sf::Font font;		//we need a font to use

	float moveDelay;
	float timer;
	bool canMove = false;
	bool active;

	int score = 0;

	void Restart();


	void Init(sf::RenderWindow& window);

	void Update(sf::RenderWindow& window, float elapsed);
	//draw everything, called once a frame. Still includes elapsed time incase anything is rotating/scaling
	void Render(sf::RenderWindow& window, float elapsed);
	//window - so you know how big the space is

	//we need to control what is going on in the game, start->play->win/lose->game over
	enum class Mode { GAME, GAME_OVER, GAME_OVER_WINNER};
	Mode mode = Mode::GAME;

	//go to the end of the objects array and add a 'newBody' object, set its grid position to the old position of the item before it in the array (prevObj)
	void IncBody()
	{
		objects.push_back(GameObj{});
		GameObj& newBody = objects.back();
		newBody.Init(*pWindow, spriteSheet, GameObj::ObjectT::SBody, *this);
		newBody.SetGridPosition(objects[objects.size() - 2].oldPos);
		newBody.prevObj = &objects[objects.size() - 2];
	}

	void TriggerGameOver()
	{
		mode = Mode::GAME_OVER;

	}

	void TriggerYouWon()
	{
		mode = Mode::GAME_OVER_WINNER;
	}
	//render displayed data (score + time alive)
	void RenderHUD(sf::RenderWindow& window, float elapsed, sf::Font & font);

	void RenderTitleScreen(sf::RenderWindow& window, float elapsed);
	//separate render function just for the game over screen
	void RenderGameOver(sf::RenderWindow & window, float elapsed);

	void RenderYouWon(sf::RenderWindow& window, float elapsed);

	//Getter and Setter class for the background grid. can spawn and check positions of the grid via coordinates (1 - 12 , 1 - 12)
	sf::Vector2f GetGridPosition(sf::Vector2i gridPos)
	{
		return grid[gridPos.x][gridPos.y].getPosition();
	}

	sf::Vector2f GetGridPosition(int x, int y)
	{
		return grid[x][y].getPosition();
	}
};

bool LoadTexture(const std::string& file, sf::Texture& tex);

#include <assert.h>
#include <string>
#include <sstream>
#include <iostream>
#include <random>
#include "Game.h"
#include <chrono>

using namespace sf;
using namespace std;


bool LoadTexture(const string& file, Texture& tex)
{
	if (tex.loadFromFile(file))
	{
		tex.setSmooth(true);
		return true;
	}
	assert(false);
	return false;
}


void Game::Init(sf::RenderWindow & window) 
{
	active = true;
	objects.reserve(256);
	pWindow = &window;
	timer = 0.0f;
	moveDelay = GC::MOVE_DELAY;

	srand(time(nullptr));
	//load the texture spritesheet and add the tile from it onto each position in the 'grid' sprite.
	LoadTexture("data/Textures.png", spriteSheet);
	for (int i = 0; i < GC::GRID_WIDTH; ++i)
	{
		for (int j = 0; j < GC::GRID_HEIGHT; ++j)
		{
			grid[i][j].setTexture(spriteSheet);
			grid[i][j].setOrigin(GC::TEX_WIDTH/2, GC::TEX_HEIGHT/2);
			grid[i][j].setTextureRect(sf::IntRect(static_cast<int>(GC::TEX_WIDTH * 4.0f), 0, static_cast<int>(GC::TEX_WIDTH), static_cast<int>(GC::TEX_HEIGHT)));
			grid[i][j].setScale((GC::SCREEN_RES.x/GC::GRID_WIDTH)/GC::TEX_WIDTH, (GC::SCREEN_RES.y / GC::GRID_HEIGHT) / GC::TEX_HEIGHT);
			grid[i][j].setPosition((GC::SCREEN_RES.x/GC::GRID_WIDTH)*i + (GC::SCREEN_RES.x / GC::GRID_WIDTH)/2,
								   (GC::SCREEN_RES.y / GC::GRID_HEIGHT) * j + (GC::SCREEN_RES.y / GC::GRID_HEIGHT) / 2);
		}
	}
	int vectorOffset = 0;

	GameObj Apple;
	objects.emplace_back(Apple);
	objects[vectorOffset].Init(window, spriteSheet, GameObj::ObjectT::Apple, *this);
	objects[vectorOffset].SetGridPosition(8, 4);
	
	++vectorOffset;
	GameObj sHead;
	objects.emplace_back(sHead);
	objects[vectorOffset].Init(window, spriteSheet, GameObj::ObjectT::SHead, *this);
	objects[vectorOffset].SetGridPosition(3,4);

}

void Game::Update(sf::RenderWindow & window, float elapsed) 
{
	
	switch (mode)
	{
	case Mode::GAME:
		timer += elapsed;
		if (timer >= moveDelay)
		{
			timer = 0.0f;
			canMove = true;
		}
		for (int i = 0; i < objects.size(); ++i)
		{
			objects[i].Update(window, elapsed);
		}
		canMove = false;

		if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::D)
			|| Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::Right))
		{
			active = false;
		}
		break;
	case Mode::GAME_OVER:
		{
			break;
		}
	case Mode::GAME_OVER_WINNER:
	{
		break;
	}
	default:
		assert(false);
	}
}

void Game::RenderGameOver(sf::RenderWindow & window, float elapsed) {
	string score_str = std::to_string(score);
	Text gameovertxt("Game over! Click [X] to Quit", font, 38);
	Text scoretxt("Score: ", font, 32);
	Text scoretxt2(score_str, font, 32);
	FloatRect gofr = gameovertxt.getGlobalBounds();
	FloatRect fr = scoretxt.getGlobalBounds();
	gameovertxt.setPosition(GC::SCREEN_RES.x / 2.f - gofr.width / 2.f, GC::SCREEN_RES.y / 2.f - gofr.width / 2.f);
	scoretxt.setPosition(GC::SCREEN_RES.x / 2.f - fr.width / 2.f, GC::SCREEN_RES.y / 2.f - fr.width / 2.f);
	scoretxt2.setPosition(GC::SCREEN_RES.x * 0.67f - fr.width / 2.f, GC::SCREEN_RES.y * 0.5f - fr.width / 2.f);
	window.draw(gameovertxt);
	window.draw(scoretxt);
	window.draw(scoretxt2);
}

void Game::RenderYouWon(sf::RenderWindow& window, float elapsed) {
	string score_str = std::to_string(score);
	Text youwontxt("You Won! Click [X] to Quit", font, 38);
	Text scoretxt("Score: ", font, 32);
	Text scoretxt2(score_str, font, 32);
	FloatRect gofr = youwontxt.getGlobalBounds();
	FloatRect fr = scoretxt.getGlobalBounds();
	youwontxt.setPosition(GC::SCREEN_RES.x / 2.f - gofr.width / 2.f, GC::SCREEN_RES.y / 2.f - gofr.width / 2.f);
	scoretxt.setPosition(GC::SCREEN_RES.x / 2.f - fr.width / 2.f, GC::SCREEN_RES.y / 2.f - fr.width / 2.f);
	scoretxt2.setPosition(GC::SCREEN_RES.x * 0.67f - fr.width / 2.f, GC::SCREEN_RES.y * 0.5f - fr.width / 2.f);
	window.draw(youwontxt);
	window.draw(scoretxt);
	window.draw(scoretxt2);
}

void Game::RenderTitleScreen(sf::RenderWindow& window, float elapsed)
{
	Text title("FRANK!", font, 50);
	title.setFillColor(sf::Color::Magenta);
	Text header("use W,A,S,D or arrow keys to begin.", font, 24);
	header.setFillColor(sf::Color::Magenta);
	FloatRect frt = title.getGlobalBounds();
	FloatRect frh = header.getGlobalBounds();
	title.setPosition(GC::SCREEN_RES.x / 2.f - frt.width / 2.f, GC::SCREEN_RES.y / 2.f - frt.width / 2.f);
	header.setPosition(GC::SCREEN_RES.x * 0.5f - frh.width / 2.f, GC::SCREEN_RES.y * 0.8f - frh.width / 2.f);
	window.draw(title);
	window.draw(header);

}

void Game::Render(sf::RenderWindow & window, float elapsed) 
{

	switch (mode)
	{
	case Mode::GAME:
		for (int i = 0; i < GC::GRID_WIDTH; ++i)
		{
			for (int j = 0; j < GC::GRID_HEIGHT; ++j)
			{
				window.draw(grid[i][j]);
			}		
		}
		for (int i = 0; i < objects.size(); ++i)
		{
			objects[i].Render(window, elapsed);
		}
		if (active == true)
		{
			RenderTitleScreen(window, elapsed);
		}
		RenderHUD(window, elapsed, font);
		break;
	case Mode::GAME_OVER:
		{
			RenderGameOver(window,elapsed);
			break;
		}
	case Mode::GAME_OVER_WINNER:
	{
		RenderYouWon(window, elapsed);
		break;
	}
	default:
		assert(false);
	}
}

void Game::RenderHUD(sf::RenderWindow& window, float elapsed, sf::Font& font)
{
	Text txt;
	font.loadFromFile("data/fonts/Comic.ttf");
	txt.setFont(font);
	txt.setCharacterSize(24);
	txt.setFillColor(sf::Color::Magenta);
	stringstream ss;
	ss << "Score: " << score;
	//print
	txt.setString(ss.str());
	txt.setPosition(GC::SCREEN_RES.x * 0.05, GC::SCREEN_RES.y * 0.01);
	window.draw(txt);
}
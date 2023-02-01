#include <assert.h>
#include <random>
#include <stdlib.h>
#include "GameObj.h"
#include "Game.h"

using namespace sf;
using namespace std;

void GameObj::InitBG(RenderWindow& window, Texture& tex)
{
	spr.setTexture(tex, true);
	const IntRect& texRect = spr.getTextureRect();
}

void GameObj::Init(RenderWindow& window, Texture& tex, ObjectT type_, Game& game)
{
	type = type_;
	active = true;
	pGame = &game;
	spr.setTexture(tex);
	switch (type)
	{
	case ObjectT::Apple:
		InitApple();
		break;
	case ObjectT::SHead:
		InitSHead();
		break;
	case ObjectT::SBody:
		InitSBody();
		break;
	default:
		assert(false);
	}
}

void GameObj::InitApple()
{
	spr.setOrigin(GC::TEX_WIDTH / 2, GC::TEX_HEIGHT / 2);
	spr.setTextureRect(sf::IntRect(static_cast<int>(GC::TEX_WIDTH * 3.0f), 0, static_cast<int>(GC::TEX_WIDTH), static_cast<int>(GC::TEX_HEIGHT)));
	spr.setScale((GC::SCREEN_RES.x / GC::GRID_WIDTH) / GC::TEX_WIDTH, (GC::SCREEN_RES.y / GC::GRID_HEIGHT) / GC::TEX_HEIGHT);
	
}

void GameObj::UpdateApple()
{
	if (gridPos == pGame->objects[1].gridPos)
	{
		SetGridPosition(rand() % GC::GRID_WIDTH, rand() % GC::GRID_HEIGHT);
		if (gridPos == pGame->objects[1].gridPos)
		{
			if (gridPos.y == GC::GRID_HEIGHT-1)
				IncGridPosition(0, -1);
			else
				IncGridPosition(0, 1);
		}
		pGame->score += 100;
		pGame->IncBody();
	}
	
}


void GameObj::InitSHead()
{
	spr.setOrigin(GC::TEX_WIDTH / 2, GC::TEX_HEIGHT / 2);
	spr.setTextureRect(sf::IntRect(static_cast<int>(GC::TEX_WIDTH * 2.0f), 0, static_cast<int>(GC::TEX_WIDTH), static_cast<int>(GC::TEX_HEIGHT)));
	spr.setScale((GC::SCREEN_RES.x / GC::GRID_WIDTH) / GC::TEX_WIDTH, (GC::SCREEN_RES.y / GC::GRID_HEIGHT) / GC::TEX_HEIGHT);
	int health = 1;
	
}

void GameObj::InitSBody()
{
	spr.setOrigin(GC::TEX_WIDTH / 2, GC::TEX_HEIGHT / 2);
	spr.setTextureRect(sf::IntRect(static_cast<int>(GC::TEX_WIDTH * 1.0f), 0, static_cast<int>(GC::TEX_WIDTH), static_cast<int>(GC::TEX_HEIGHT)));
	spr.setScale((GC::SCREEN_RES.x / GC::GRID_WIDTH) / GC::TEX_WIDTH, (GC::SCREEN_RES.y / GC::GRID_HEIGHT) / GC::TEX_HEIGHT);
}

void GameObj::UpdateSBody()
{
	if (pGame->canMove)
		SetGridPosition(prevObj->oldPos);

	if (gridPos == pGame->objects[1].gridPos)
	{
		pGame->TriggerGameOver();
	}
}

void GameObj::Update(RenderWindow& window, float elapsed)
{

	if (active)
	{
		
		switch (type)
		{
		case ObjectT::SHead:
			PlayerControl(window.getSize(), elapsed);
			break;
		case ObjectT::SBody:
			UpdateSBody();
			break;
		case ObjectT::Apple:
			UpdateApple();
			break;
		}
	}
}


void GameObj::Render(RenderWindow& window, float elapsed)
{
	if (active)
		window.draw(spr);
}


void GameObj::PlayerControl(const Vector2u& screenSz, float elapsed)
{	
	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
	{
		yVel = -1;
		xVel = 0;
		spr.setRotation(270);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
	{
		yVel = 1;
		xVel = 0;
		spr.setRotation(90);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
	{
		yVel = 0;
		xVel = -1;
		spr.setRotation(180);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
	{
		yVel = 0;
		xVel = 1;
		spr.setRotation(0);
	}

	if (pGame->canMove)
	{
		IncGridPosition(xVel, yVel);
	}
}


void GameObj::IncGridPosition(int xVelocity, int yVelocity)
{
	oldPos = gridPos;
	gridPos.x += xVelocity;
	gridPos.y += yVelocity;
	if (gridPos.x > GC::GRID_WIDTH || gridPos.x < 0 || gridPos.y > GC::GRID_HEIGHT || gridPos.y < 0)
	{
		//END THE GAME HERE WITH CODE
		pGame->TriggerGameOver();
		return;
	}

	if (pGame->score == 14400)
	{
		pGame->TriggerYouWon();
	 return;
	}

	if (pGame)
	{
		spr.setPosition(pGame->GetGridPosition(gridPos));
	}
	else
		assert(false);

	
}

void GameObj::SetGridPosition(sf::Vector2i pos)
{
	oldPos = gridPos;
	gridPos = pos;
	if (pGame)
	{
		spr.setPosition(pGame->GetGridPosition(pos));
	}
	else
		assert(false);
}
void GameObj::SetGridPosition(int xVelocity, int yVelocity)
{
	oldPos = gridPos;
	gridPos.x = xVelocity;
	gridPos.y = yVelocity;
	if (pGame)
	{
		spr.setPosition(pGame->GetGridPosition(xVelocity, yVelocity));
	}
	else
		assert(false);
}
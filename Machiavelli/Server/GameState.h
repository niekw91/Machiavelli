#pragma once
#include "Game.h"
// Forward declaration
//class Game;

class GameState
{
public:
	GameState();

	virtual void Init(Game &game) = 0;
	virtual void Cleanup(Game &game) = 0;

	virtual void HandleEvents(Game &game) = 0;
	virtual void Update(Game &game) = 0;
	
};


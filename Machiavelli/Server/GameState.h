#pragma once
#include "Game.h"
#include <memory>
#include "GameStateManager.h"
// Forward declaration
//class Game;

class GameState
{
public:
	GameState();
	virtual ~GameState();

	virtual void Init(shared_ptr<Game> &game) = 0;
	virtual void Cleanup(shared_ptr<Game> &game) = 0;

	virtual void HandleEvents(shared_ptr<Game> &game) = 0;
	virtual void Update(shared_ptr<Game> &game) = 0;
};


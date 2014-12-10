#pragma once
#include "GameState.h"

// Forward declaration
class Game;

class GameOverState :
	public GameState
{
public:
	GameOverState();
	~GameOverState();

	void Init(Game &game);
	void Cleanup(Game &game);

	void HandleEvents(Game &game);
	void Update(Game &game);
};


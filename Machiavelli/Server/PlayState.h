#pragma once
#include "GameState.h"

// Forward declaration
class Game;

class PlayState :
	public GameState
{
public:
	PlayState();
	~PlayState();

	void Init(Game &game);
	void Cleanup(Game &game);

	void HandleEvents(Game &game);
	void Update(Game &game);
};


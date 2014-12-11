#pragma once
#include "GameState.h"
//#include <memory>

// Forward declaration
class Game;

class GameOverState :
	public GameState
{
public:
	GameOverState();
	~GameOverState();

	void Init(shared_ptr<Game> &game);
	void Cleanup(shared_ptr<Game> &game);

	void HandleEvents(shared_ptr<Game> &game);
	void Update(shared_ptr<Game> &game);
};


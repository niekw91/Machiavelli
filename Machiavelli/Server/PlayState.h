#pragma once
#include "GameState.h"
//#include <memory>

// Forward declaration
class Game;

class PlayState :
	public GameState
{
public:
	PlayState();
	~PlayState();

	void Init(shared_ptr<Game> &game);
	void Cleanup(shared_ptr<Game> &game);

	void HandleEvents(shared_ptr<Game> &game);
	void Update(shared_ptr<Game> &game);
};


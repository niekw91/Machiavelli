#pragma once
#include "GameState.h"

// Forward declaration
class Game;

class WaitingRoomState :
	public GameState
{
public:
	WaitingRoomState();
	~WaitingRoomState();

	void Init(shared_ptr<Game> &game);
	void Cleanup(shared_ptr<Game> &game);

	void HandleEvents(shared_ptr<Game> &game);
	void Update(shared_ptr<Game> &game);
private:
	bool _showWelcomeMessage;
};
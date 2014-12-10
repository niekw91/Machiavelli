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

	void Init(Game &game);
	void Cleanup(Game &game);

	void HandleEvents(Game &game);
	void Update(Game &game);
};
#pragma once
#include "Player.h"
#include "PlayerStateMachine.h"
#include "Socket.h"

#include <memory>

class PlayerState
{
public:
	PlayerState() { }
	~PlayerState() { }

	virtual void Init(shared_ptr<Player> &player) = 0;
	virtual void Cleanup(shared_ptr<Player> &player) = 0;

	virtual void HandleEvents(shared_ptr<Player> &player) = 0;
	virtual void Update(shared_ptr<Player> &player) = 0;
};


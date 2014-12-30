#pragma once
#include "PlayerState.h"

class KingState :
	public PlayerState
{
public:
	KingState();
	~KingState();

	void Init(shared_ptr<Player> &player, shared_ptr<Game> &game);
	void Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game);

	void HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game);
	void Update(shared_ptr<Player> &player, shared_ptr<Game> &game);

	void UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game);
};


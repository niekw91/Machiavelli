#pragma once
#include "PlayerState.h"

class WarlordState :
	public PlayerState
{
public:
	WarlordState();
	~WarlordState();

	void Init(shared_ptr<Player> &player, shared_ptr<Game> &game);
	void Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game);

	void HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game);
	void Update(shared_ptr<Player> &player, shared_ptr<Game> &game);

	void UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game);
};


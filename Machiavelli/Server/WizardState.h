#pragma once
#include "PlayerState.h"

class Player;

class WizardState :
	public PlayerState
{
public:
	WizardState();
	~WizardState();

	void Init(shared_ptr<Player> &player);
	void Cleanup(shared_ptr<Player> &player);

	void HandleEvents(shared_ptr<Player> &player);
	void Update(shared_ptr<Player> &player);
};


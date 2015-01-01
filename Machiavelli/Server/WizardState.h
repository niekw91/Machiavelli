#pragma once
#include "PlayerState.h"

class WizardState :
	public PlayerState
{
public:
	WizardState();
	~WizardState();

	void Init(shared_ptr<Player> &player, shared_ptr<Game> &game);
	void Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game);

	void HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game);
	void Update(shared_ptr<Player> &player, shared_ptr<Game> &game);

	void UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game);

private:
	void SwitchCards();
};


#pragma once
#include "PlayerState.h"

class Player;

class MerchantState :
	public PlayerState
{
public:
	MerchantState();
	~MerchantState();


	void Init(shared_ptr<Player> &player);
	void Cleanup(shared_ptr<Player> &player);

	void HandleEvents(shared_ptr<Player> &player);
	void Update(shared_ptr<Player> &player);
};


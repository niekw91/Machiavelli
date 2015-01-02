#pragma once
#include "Player.h"
#include "Game.h"
#include "ClientCommand.h"
#include "Socket.h"
#include "PlayerStateMachine.h"

#include <memory>

class PlayerState
{
public:
	PlayerState() { }
	~PlayerState() { }

	virtual void Init(shared_ptr<Player> &player, shared_ptr<Game> &game) = 0;
	virtual void Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game) = 0;

	virtual void HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game) = 0;
	virtual void Update(shared_ptr<Player> &player, shared_ptr<Game> &game) = 0;

	virtual void UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game) = 0;

	void Render(shared_ptr<Player> &player, std::string character);
	void RenderChoices(shared_ptr<Player> &player);
	void RenderBuildings(shared_ptr<Player> &player);
	void RenderCardsInHand(shared_ptr<Player> &player);
	int HandleChoice(shared_ptr<Player> &player, shared_ptr<Game> &game, int range);
	void HandleTurn(shared_ptr<Player> &player, shared_ptr<Game> &game, int choice);

	void LookAtOpponent(shared_ptr<Player> &player, shared_ptr<Game> &game);
	void TakeGold(shared_ptr<Player> &player, shared_ptr<Game> &game, int amount);
	void TakeBuildingCards(shared_ptr<Player> &player, shared_ptr<Game> &game, int amount);
};


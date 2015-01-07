#pragma once
#include "Player.h"
#include "Game.h"
#include "ClientCommand.h"
#include "Socket.h"
#include "PlayerStateMachine.h"
#include "Option.h"

#include <memory>
#include <vector>

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
	void ResetChoices(shared_ptr<Player> &player, shared_ptr<Game> &game, string character);
	void ResetChoices(shared_ptr<Player> &player, shared_ptr<Game> &game);
	int GetNumberOfChoices() { return _basicChoices.size(); }
	void RemoveChoice(int index);
	void RenderChoices(shared_ptr<Player> &player);
	void RenderBuildings(shared_ptr<Player> &player);
	void RenderCardsInHand(shared_ptr<Player> &player);
	int HandleChoice(shared_ptr<Player> &player, shared_ptr<Game> &game, int range);
	void HandleTurn(shared_ptr<Player> &player, shared_ptr<Game> &game, int choice);

	void LookAtOpponent(shared_ptr<Player> &player, shared_ptr<Game> &game);
	void TakeGold(shared_ptr<Player> &player, shared_ptr<Game> &game, int amount);
	void TakeBuildingCards(shared_ptr<Player> &player, shared_ptr<Game> &game, int amount);
	void Build(shared_ptr<Player> &player, shared_ptr<Game> &game);
	std::string GetColor(int color);
private:
	vector<Option> _basicChoices;

	int _numberToDraw = 2;
	int _numberToDiscard = 1;
protected:
	bool _endTurn;
};


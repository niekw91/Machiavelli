#pragma once
#include "GameState.h"

class Game;

class PickCardState :
	public GameState
{
public:
	PickCardState();
	~PickCardState();

	void Init(shared_ptr<Game> &game);
	void Cleanup(shared_ptr<Game> &game);

	void HandleEvents(shared_ptr<Game> &game);
	void Update(shared_ptr<Game> &game);

	CharacterCard PickCard(shared_ptr<Player> &player, shared_ptr<Game> &game);
	void HandleTurn(shared_ptr<Player> &player, shared_ptr<Game> &game);
	int HandleChoice(shared_ptr<Player> &player, shared_ptr<Game> &game, int range);
};
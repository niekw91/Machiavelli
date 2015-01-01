#pragma once
#include "GameState.h"

class Player;
class Game;

class PlayState :
	public GameState
{
public:
	PlayState();
	~PlayState();

	void Init(shared_ptr<Game> &game);
	void Cleanup(shared_ptr<Game> &game);

	void HandleEvents(shared_ptr<Game> &game);
	void Update(shared_ptr<Game> &game);
private:
	shared_ptr<Player> HasCharacterCard(Game::Character character, shared_ptr<Game> &game);
	void StealGold(Game::Character character, shared_ptr<Game> &game);
};


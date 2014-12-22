#pragma once
#include "GameState.h"

#include <queue>
#include <map>

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
	enum Character { ARCHITECT, ASSASSIN, BISHOP, KING, MERCHANT, THIEF, WARLORD, WIZARD };
	std::map<Character, std::string> _characterMap;
	std::queue<Character> _orderQueue;

	void GenerateOrder();
	void GenerateMap();
	shared_ptr<Player> HasCharacterCard(Character character, shared_ptr<Game> &game);
};


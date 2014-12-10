#pragma once
#include <vector>

class Player;

class Game
{
public:
	Game();
	virtual ~Game();

	void AddPlayer();
	int GetPlayerCount();
private:
	std::vector<Player*> _players;
};


#pragma once
#include <vector>
#include <memory>

using namespace std;

// Forward declaration
class Player;
class GameStateManager;

class Game
{
public:
	Game();
	virtual ~Game();

	void Init();
	void Cleanup();

	void Start();
	void Stop();

	void HandleEvents();
	void Update();

	unique_ptr<GameStateManager> &GetStateManager() { return _stateManager; }
	vector<unique_ptr<Player>> &GetPlayers() { return _players; }

	/*void AddPlayer();
	int GetPlayerCount();*/

private:
	unique_ptr<GameStateManager> _stateManager;
	vector<unique_ptr<Player>> _players;

	bool _running;
};


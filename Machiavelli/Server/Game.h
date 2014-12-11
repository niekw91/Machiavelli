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

	void Init(shared_ptr<Game> &game);
	void Cleanup();

	void Start(shared_ptr<Game> &game);
	void Stop();

	void HandleEvents(shared_ptr<Game> &game);
	void Update(shared_ptr<Game> &game);

	shared_ptr<GameStateManager> &GetStateManager() { return _stateManager; }
	//shared_ptr<vector<shared_ptr<Player>>> &GetPlayers() { return _players; }

	/*void AddPlayer();
	int GetPlayerCount();*/

private:
	shared_ptr<GameStateManager> _stateManager;
	//shared_ptr<vector<shared_ptr<Player>>> _players;

	bool _running;
};


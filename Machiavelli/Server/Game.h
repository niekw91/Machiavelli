#pragma once
#include <vector>
#include <queue>
#include <memory>
#include "ClientCommand.h"

using namespace std;

// Forward declaration
class Player;
class GameStateManager;
class Socket;

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

	void AddCommand(ClientCommand command);
	bool HasNextCommand();
	ClientCommand GetNextCommand();

	shared_ptr<GameStateManager> &GetStateManager() { return _stateManager; }
	shared_ptr<vector<shared_ptr<Player>>> &GetPlayers() { return _players; }

	void AddPlayer(shared_ptr<Socket> client);
	int GetPlayerCount();

private:
	shared_ptr<GameStateManager> _stateManager;
	shared_ptr<vector<shared_ptr<Player>>> _players;
	shared_ptr<std::queue<ClientCommand>> _commands;

	bool _running;
};


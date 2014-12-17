#pragma once
#include <vector>
#include <queue>
#include <memory>

#include "ClientCommand.h"
#include "CardStack.h"
#include "CharacterCard.h"
#include "BuildingCard.h"
#include "CardFactory.h"

using namespace std;

// Forward declaration
class Player;
class GameStateManager;
class Socket;

class Game : public enable_shared_from_this<Game>
{
public:
	Game();
	virtual ~Game();

	void Init();
	void Cleanup();

	void Start();
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

	void AddCharacterCard(shared_ptr<CharacterCard> card);
	void AddBuildingCard(shared_ptr<BuildingCard> card);

private:
	shared_ptr<GameStateManager> _stateManager;
	shared_ptr<vector<shared_ptr<Player>>> _players;
	shared_ptr<std::queue<ClientCommand>> _commands;

	shared_ptr<CardStack<CharacterCard>> _characterCards;
	shared_ptr<CardStack<BuildingCard>> _buildingCards;

	shared_ptr<CardFactory> _factory;

	bool _running;
};


#pragma once
#include <vector>
#include <queue>
#include <memory>
#include <queue>
#include <map>

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
	enum Character { ARCHITECT, ASSASSIN, BISHOP, KING, MERCHANT, THIEF, WARLORD, WIZARD };

	Game();
	virtual ~Game();

	void Init();
	void Cleanup();

	void Start();
	void Stop();

	void HandleEvents(shared_ptr<Game> &game);
	void Update(shared_ptr<Game> &game);

	void AddCommand(ClientCommand command);
	bool HasNextCommand(shared_ptr<Player> &player);
	ClientCommand GetNextCommand(shared_ptr<Player> &player);

	shared_ptr<GameStateManager> &GetStateManager() { return _stateManager; }
	shared_ptr<vector<shared_ptr<Player>>> &GetPlayers() { return _players; }
	shared_ptr<CardStack<CharacterCard>> &GetCharacterCards() { return _characterCards; }
	shared_ptr<CardStack<BuildingCard>> &GetBuildingCards() { return _buildingCards; }

	void AddPlayer(shared_ptr<Socket> &client);
	int GetPlayerCount();

	void AddCharacterCard(CharacterCard card);
	void AddBuildingCard(BuildingCard card);
	void AddGold(int amount);
	int RemoveGold(int amount);

	void GenerateOrder();
	void KillCharacter(Character character);
	void GenerateMap();
	shared_ptr<std::queue<Character>> GetOrderQueue() { return _orderQueue; }
	shared_ptr<std::map<Game::Character, std::string>> GetCharacterMap() { return _characterMap; }
	bool HasBeenKilled(Character character) { return _flagForKill == character; }
private:
	const int GOLD_AMOUNT{ 30 };

	shared_ptr<GameStateManager> _stateManager;
	shared_ptr<vector<shared_ptr<Player>>> _players;
	shared_ptr<std::queue<ClientCommand>> _commands;

	shared_ptr<std::queue<Character>> _orderQueue;
	shared_ptr<std::map<Game::Character, std::string>> _characterMap;
	Character _flagForKill;

	shared_ptr<CardStack<CharacterCard>> _characterCards;
	shared_ptr<CardStack<BuildingCard>> _buildingCards;

	shared_ptr<CardFactory> _factory;

	int _gold;

	bool _running;
};


#pragma once
#include <memory>

#include "CardStack.h"
#include "CharacterCard.h"
#include "BuildingCard.h"

class Socket;
class Game;
class PlayerStateMachine;

using namespace std;

class Player
{
public:
	Player(shared_ptr<Socket> &socket, shared_ptr<Game> &game);
	virtual ~Player();

	shared_ptr<Socket> GetClient() { return _client; }

	void SetCrown(bool crown);
	bool HasCrown();

	void AddCharacterCard(CharacterCard card);
	void RemoveCharacterCard(int index);
	shared_ptr<CardStack<CharacterCard>> GetCharacterCards() { return _characterCards; }
	BuildingCard GetBuildingCard(int index);
	void AddBuildingCard(BuildingCard card);
	void Build(BuildingCard card);
	int NumberOfCharacterCards() { return _characterCards->Size(); }
	int GetGoldAmount() { return _gold;  }
	void AddGold(int amount) { _gold += amount; }
	void RemoveGold(int amount) { _gold -= amount; }
	shared_ptr<PlayerStateMachine> GetStateMachine() { return _stateMachine; }
private:
	shared_ptr<PlayerStateMachine> _stateMachine;
	shared_ptr<Socket> _client;
	shared_ptr<Game> _game;

	bool _hasCrown;

	int _gold;

	shared_ptr<CardStack<CharacterCard>> _characterCards;
	shared_ptr<CardStack<BuildingCard>> _buildingCards;
	shared_ptr<CardStack<BuildingCard>> _buildings;
};


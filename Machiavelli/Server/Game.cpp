#include "Game.h"
#include "Player.h"
#include "GameStateManager.h"
#include "Server.h"
#include "Socket.h"
#include "ClientCommand.h"

#include <thread>

Game::Game() 
{
	_commands = make_shared<std::queue<ClientCommand>>();
	_players = make_shared<vector<shared_ptr<Player>>>();
	_factory = make_shared<CardFactory>();
	_buildingCards = make_shared<CardStack<BuildingCard>>();
	_characterCards = make_shared<CardStack<CharacterCard>>();
	_characterMap = make_shared<std::map<Game::Character, std::string>>();
	_orderQueue = make_shared<std::queue<Character>>();

	_gold = GOLD_AMOUNT;
}

Game::~Game() 
{
}

void Game::Init() 
{
	// Start server
	thread server{ Server::Start, shared_from_this() };
	server.detach();

	// Load cards from file
	_factory->CreateCharacterCardsFromFile("assets/cards/charactercards.csv", shared_from_this());
	_factory->CreateBuildingCardsFromFile("assets/cards/buildingcards.csv", shared_from_this());

	// Create statemanager
	_stateManager = make_shared<GameStateManager>(shared_from_this());

	// Start running
	_running = true;
}

void Game::Cleanup() 
{

}

void Game::Start()
{
	// Start game
	while (_running) {
		HandleEvents(shared_from_this());
		Update(shared_from_this());
	}
}

void Game::Stop() 
{
	_running = false;
}

void Game::HandleEvents(shared_ptr<Game> &game)
{
	_stateManager->HandleEvents(game);
}

void Game::Update(shared_ptr<Game> &game)
{
	_stateManager->Update(game);
}

void Game::AddCommand(ClientCommand command)
{
	_commands->push(command);
}

bool Game::HasNextCommand(shared_ptr<Player> &player) {
	bool has = false;

	if (_commands->size() > 0)  {
		ClientCommand command = _commands->front();
		if (command.get_client() == player->GetClient())
			has = true;
	}
	return has;
}

ClientCommand Game::GetNextCommand(shared_ptr<Player> &player)
{
	while (_commands->front().get_client() != player->GetClient())
		_commands->pop();
	ClientCommand command = _commands->front();
	_commands->pop();
	return command;
}

void Game::AddPlayer(shared_ptr<Socket> &client)
{
	_players->push_back(make_unique<Player>(client, shared_from_this()));
}

int Game::GetPlayerCount() 
{
	return _players->size();
}

void Game::AddBuildingCard(BuildingCard card)
{
	_buildingCards->AddCard(card);
}

void Game::AddCharacterCard(CharacterCard card)
{
	_characterCards->AddCard(card);
}

void Game::AddGold(int amount)
{
	if (!(_gold += amount) > 30)
		_gold += amount;
}

int Game::RemoveGold(int amount)
{
	if (!(_gold -= amount) < 0) {
		_gold -= amount;
		return amount;
	}
	else {
		return -1;
	}
}

void Game::KillCharacter(Character character)
{
	_flagForKill = character;
}

void Game::GenerateOrder()
{
	_orderQueue->push(ASSASSIN);
	_orderQueue->push(THIEF);
	_orderQueue->push(WIZARD);
	_orderQueue->push(KING);
	_orderQueue->push(BISHOP);
	_orderQueue->push(MERCHANT);
	_orderQueue->push(ARCHITECT);
	_orderQueue->push(WARLORD);
}

void Game::GenerateMap()
{
	_characterMap->insert(std::make_pair(ASSASSIN, "Assassin"));
	_characterMap->insert(std::make_pair(THIEF, "Thief"));
	_characterMap->insert(std::make_pair(WIZARD, "Wizard"));
	_characterMap->insert(std::make_pair(KING, "King"));
	_characterMap->insert(std::make_pair(BISHOP, "Bishop"));
	_characterMap->insert(std::make_pair(MERCHANT, "Merchant"));
	_characterMap->insert(std::make_pair(ARCHITECT, "Architect"));
	_characterMap->insert(std::make_pair(WARLORD, "Warlord"));
}

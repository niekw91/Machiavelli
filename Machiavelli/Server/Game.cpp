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
	SetGameStart(true);
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

	while (_commands->size() > 1) {
		if (_commands->front().get_client() != player->GetClient())
			_commands->pop();
	}
	if (!_commands->empty()) {
		if (_commands->front().get_client() != player->GetClient())
			_commands->pop();
		else
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
	_gold += amount;
	if (_gold > GOLD_AMOUNT)
		_gold = GOLD_AMOUNT;
}

int Game::RemoveGold(int amount)
{
	if ((_gold -= amount) < 0) {
		return -1;
	}
	else {
		return amount;
	}
}

void Game::KillCharacter(Character character)
{
	_flagForKill = character;
}

void Game::StealFrom(Character character)
{
	_flagForSteal = character;
}

shared_ptr<Player> Game::GetOpponent(shared_ptr<Player> &player)
{
	// Determine opponent
	shared_ptr<Player> opponent;
	if (GetPlayers()->front() == player)
		opponent = GetPlayers()->back();
	else
		opponent = GetPlayers()->front();
	return opponent;
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

void Game::ResetRound(bool isStart)
{
	if (isStart) {
		shared_ptr<CardStack<BuildingCard>> bCards = _factory->GetBuildingCards();
		_buildingCards->Clear();
		for (size_t i = 0, blen = bCards->Size(); i < blen; ++i)
			_buildingCards->AddCard(bCards->ShowCardByIndex(i));
	}

	shared_ptr<CardStack<CharacterCard>> cCards = _factory->GetCharacterCards();

	_characterCards->Clear();

	for (size_t i = 0, clen = cCards->Size(); i < clen; ++i)
		_characterCards->AddCard(cCards->ShowCardByIndex(i));

	for (size_t i = 0, plen = _players->size(); i < plen; ++i) {
		_players->at(i)->GetCharacterCards()->Clear();
	}

	_flagForKill = LAST_CHARACTER;
	_flagForSteal = LAST_CHARACTER;

	GenerateOrder();
}

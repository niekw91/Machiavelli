#include "Game.h"
#include "Player.h"
#include "GameStateManager.h"
#include "Server.h"
#include "Socket.h"

#include <thread>

Game::Game() 
{
	_commands = make_shared<std::queue<ClientCommand>>();
	_players = make_shared<vector<shared_ptr<Player>>>();
}

Game::~Game() 
{
}

void Game::Init(shared_ptr<Game> &game) 
{
	// Start server
	thread server{ Server::Start, game };
	server.detach();

	// Create statemanager
	_stateManager = make_shared<GameStateManager>(game);

	// Start running
	_running = true;
}

void Game::Cleanup() 
{

}

void Game::Start(shared_ptr<Game> &game)
{
	// Start game
	while (_running) {
		HandleEvents(game);
		Update(game);
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

bool Game::HasNextCommand() {
	return _commands->size() > 0;
}

ClientCommand Game::GetNextCommand()
{
	ClientCommand command = _commands->front();
	_commands->pop();
	return command;
}

void Game::AddPlayer(shared_ptr<Socket> client)
{
	_players->push_back(make_unique<Player>(client));
}

int Game::GetPlayerCount() 
{
	return _players->size();
}

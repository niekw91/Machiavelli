#include "Game.h"
#include "Player.h"
#include "GameStateManager.h"

Game::Game() 
{
}

Game::~Game() 
{
}

void Game::Init(shared_ptr<Game> &game) 
{
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

//void Game::AddPlayer() 
//{
//	_players.push_back(make_unique<Player>());
//}

//int Game::GetPlayerCount() 
//{
//	return _players.size();
//}

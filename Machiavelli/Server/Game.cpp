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
	_stateManager = make_shared<GameStateManager>();
	_stateManager->Init(game);

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
		HandleEvents();
		Update();
	}
}

void Game::Stop() 
{
	_running = false;
}

void Game::HandleEvents() 
{
	//_stateManager->HandleEvents(make_shared<Game>(this));
}

void Game::Update() 
{
	//_stateManager->Update(make_shared<Game>(this));
}

//void Game::AddPlayer() 
//{
//	_players.push_back(make_unique<Player>());
//}

//int Game::GetPlayerCount() 
//{
//	return _players.size();
//}

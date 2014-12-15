#include "Game.h"
#include "Player.h"
#include "GameStateManager.h"

Game::Game() 
{
}

Game::~Game() 
{
}

void Game::Init() 
{
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
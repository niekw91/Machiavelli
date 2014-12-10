#include "GameStateManager.h"
#include "Game.h"
#include "GameState.h"
#include "WaitingRoomState.h"

GameStateManager::GameStateManager(Game &game)
{
	PushState(game, *make_unique<WaitingRoomState>());
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::Init(Game &game)
{
	//_states.push_back(make_unique<WaitingRoomState>());
}

void GameStateManager::Cleanup(Game &game)
{
	// Cleanup states
	while (!_states.empty()){
		_states.back()->~GameState();
		_states.pop_back();
	}
}

void GameStateManager::ChangeState(Game &game, GameState &state)
{
	// cleanup the current state
	if (!_states.empty()) {
		_states.back()->Cleanup(game);
		_states.pop_back();
	}

	// store and init the new state
	_states.push_back(make_unique<GameState>(state));
	_states.back()->Init(game);
}

void GameStateManager::PushState(Game &game, GameState &state) 
{
	// store and init the new state
	_states.push_back(make_unique<GameState>(state));
	_states.back()->Init(game);
}

void GameStateManager::PopState(Game &game)
{
	// cleanup the current state
	if (!_states.empty()) {
		_states.back()->Cleanup(game);
		_states.pop_back();
	}
}

void GameStateManager::HandleEvents(Game &game)
{
	// handle events of current state
	_states.back()->HandleEvents(game);
}

void GameStateManager::Update(Game &game)
{
	// update current state
	_states.back()->Update(game);
}

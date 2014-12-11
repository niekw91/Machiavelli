#include "GameStateManager.h"
#include "Game.h"
#include "GameState.h"
#include "WaitingRoomState.h"

GameStateManager::GameStateManager()
{
	
}

GameStateManager::~GameStateManager()
{

}

void GameStateManager::Init(shared_ptr<Game> &game)
{
	//PushState(game, dynamic_pointer_cast<GameState>(make_shared<WaitingRoomState>()));
}

void GameStateManager::Cleanup(shared_ptr<Game> &game)
{
	// Cleanup states
	while (!_states.empty()){
		_states.back()->~GameState();
		_states.pop_back();
	}
}

void GameStateManager::ChangeState(shared_ptr<Game> &game, shared_ptr<GameState> &state)
{
	// cleanup the current state
	if (!_states.empty()) {
		_states.back()->Cleanup(game);
		_states.pop_back();
	}

	// store and init the new state
	_states.push_back(state);
	_states.back()->Init(game);
}

void GameStateManager::PushState(shared_ptr<Game> &game, shared_ptr<GameState> &state)
{
	// store and init the new state
	_states.push_back(state);
	_states.back()->Init(game);
}

void GameStateManager::PopState(shared_ptr<Game> &game)
{
	// cleanup the current state
	if (!_states.empty()) {
		_states.back()->Cleanup(game);
		_states.pop_back();
	}
}

void GameStateManager::HandleEvents(shared_ptr<Game> &game)
{
	// handle events of current state
	_states.back()->HandleEvents(game);
}

void GameStateManager::Update(shared_ptr<Game> &game) 
{
	// update current state
	_states.back()->Update(game);
}

//// The workaround to take a shared_ptr<T> where T publicly derives from Base
//template <typename T>
//auto PushState(shared_ptr<Game>, shared_ptr<T>& pd) ->
//decltype(PushState(shared_ptr<Game>, shared_ptr<GameState>(pd))) {
//	return PushState(shared_ptr<Game>, shared_ptr<GameState>(pd));
//}
#include "PlayerStateMachine.h"
#include "Player.h"
#include "PlayerState.h"

PlayerStateMachine::PlayerStateMachine() {
}


PlayerStateMachine::~PlayerStateMachine() {
}

void PlayerStateMachine::Init(shared_ptr<Player> &player)
{

}

void PlayerStateMachine::Cleanup(shared_ptr<Player> &player)
{
	// Cleanup states
	while (!_states.empty()){
		_states.back()->~PlayerState();
		_states.pop_back();
	}
}

void PlayerStateMachine::ChangeState(shared_ptr<Player> &player, shared_ptr<PlayerState> &state)
{
	// cleanup the current state
	if (!_states.empty()) {
		_states.back()->Cleanup(player);
		_states.pop_back();
	}

	// store and init the new state
	_states.push_back(state);
	_states.back()->Init(player);
}

void PlayerStateMachine::PushState(shared_ptr<Player> &player, shared_ptr<PlayerState> &state)
{
	// store and init the new state
	_states.push_back(state);
	_states.back()->Init(player);
}

void PlayerStateMachine::PopState(shared_ptr<Player> &player)
{
	// cleanup the current state
	if (!_states.empty()) {
		_states.back()->Cleanup(player);
		_states.pop_back();
	}
}

void PlayerStateMachine::HandleEvents(shared_ptr<Player> &player)
{
	// handle events of current state
	_states.back()->HandleEvents(player);
}

void PlayerStateMachine::Update(shared_ptr<Player> &player)
{
	// update current state
	_states.back()->Update(player);
}
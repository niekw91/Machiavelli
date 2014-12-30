#include "WaitingRoomState.h"
#include "PickCardState.h"
#include "Game.h"
#include "Player.h"

WaitingRoomState::WaitingRoomState()
{
}

WaitingRoomState::~WaitingRoomState()
{
}

void WaitingRoomState::Init(shared_ptr<Game> &game)
{
	_showWelcomeMessage = true;
}

void WaitingRoomState::Cleanup(shared_ptr<Game> &game)
{

}

void WaitingRoomState::HandleEvents(shared_ptr<Game> &game)
{

}

void WaitingRoomState::Update(shared_ptr<Game> &game)
{
	if (game->GetPlayerCount() == 2) {
		game->GetStateManager()->ChangeState(game, dynamic_pointer_cast<GameState>(make_shared<PickCardState>()));
	}
	else {
		if (_showWelcomeMessage) {
			auto players = game->GetPlayers();
			if (players->size() == 1) {
				players->at(0)->GetClient()->writeline("Welcome to Machiavelli, please wait for a second player..");
				_showWelcomeMessage = false;
			}
		}
	}
}
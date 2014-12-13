#include "WaitingRoomState.h"
#include "PlayState.h"
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
		game->GetStateManager()->ChangeState(game, dynamic_pointer_cast<GameState>(make_shared<PlayState>()));
	}
	else {
		if (_showWelcomeMessage) {
			shared_ptr<vector<shared_ptr<Player>>> players = game->GetPlayers();
			if (players->size() == 1) {
				players->at(0)->GetClient()->write("Welcome to Machiavelli, please wait for a second player..\n");
				_showWelcomeMessage = false;
			}
		}
	}
}
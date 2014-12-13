#include "PlayState.h"
#include "Game.h"
#include "Player.h"


PlayState::PlayState()
{
}


PlayState::~PlayState()
{
}

void PlayState::Init(shared_ptr<Game> &game)
{
	std::cout << "Game: 2 player connected, starting game" << std::endl;
	shared_ptr<vector<shared_ptr<Player>>> players = game->GetPlayers();
	for (int i = 0; i < players->size(); i++) {
		players->at(i)->GetClient()->write("Starting game!\n");
	}
}

void PlayState::Cleanup(shared_ptr<Game> &game)
{

}

void PlayState::HandleEvents(shared_ptr<Game> &game)
{

}

void PlayState::Update(shared_ptr<Game> &game)
{

}
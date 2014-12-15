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
	auto players = game->GetPlayers();
	for (size_t i = 0, ilen = players->size(); i < ilen; ++i) {
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
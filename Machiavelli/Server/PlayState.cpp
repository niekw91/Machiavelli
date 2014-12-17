#include "PlayState.h"
#include "CardStack.h"
#include "Game.h"
#include "Player.h"
#include "Random.h"

PlayState::PlayState()
{
}


PlayState::~PlayState()
{
}

void PlayState::Init(shared_ptr<Game> &game)
{
	std::cerr << "Game: 2 player connected, starting game" << std::endl;
	auto players = game->GetPlayers();

	// Create building cards
	


	// Pick random player to have the crown
	players->at(Random::Next(0, players->size() - 1))->SetCrown(true);

	for (size_t i = 0, ilen = players->size(); i < ilen; ++i) {
		players->at(i)->GetClient()->write("Starting game!\n");
	}

}

void PlayState::Cleanup(shared_ptr<Game> &game)
{

}

void PlayState::HandleEvents(shared_ptr<Game> &game)
{
	if (game->HasNextCommand()) {
		ClientCommand command = game->GetNextCommand();
		auto players = game->GetPlayers();
		for (size_t i = 0, ilen = players->size(); i < ilen; ++i) {
			if (players->at(i)->GetClient() == command.get_client()) {

			}
		}
		
	}
}

void PlayState::Update(shared_ptr<Game> &game)
{
	// Spelers kaarten laten kiezen
}
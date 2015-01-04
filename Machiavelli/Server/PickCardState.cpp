#include "PickCardState.h"
#include "CardStack.h"
#include "Game.h"
#include "Player.h"
#include "Random.h"
#include "Server.h"
#include "PlayState.h"

PickCardState::PickCardState()
{
}


PickCardState::~PickCardState()
{
}

void PickCardState::Init(shared_ptr<Game> &game)
{
	game->ResetRound(game->IsGameStart());

	if (game->IsGameStart()) {
		game->GenerateMap();

		std::cerr << "Game: 2 player connected, starting game.\r\n";
		auto players = game->GetPlayers();

		// Pick random player to have the crown
		int random = Random::Next(0, players->size() - 1);
		players->at(random)->SetCrown(true);
		players->at(random)->GetClient()->writeline("You have been given the crown!\r\n");

		// Give each player 2 gold peices and 4 building cards
		for (size_t i = 0, ilen = players->size(); i < ilen; ++i) {
			int amount = game->RemoveGold(2);
			if (amount != -1)
				players->at(i)->AddGold(2);
			for (size_t b = 0; b < 4; b++)
				players->at(i)->AddBuildingCard(game->GetBuildingCards()->GetRandomCard());
		}

		game->SetGameStart(false);
	}
}

void PickCardState::Cleanup(shared_ptr<Game> &game)
{

}

void PickCardState::HandleEvents(shared_ptr<Game> &game)
{

}

void PickCardState::Update(shared_ptr<Game> &game)
{
	auto players = game->GetPlayers();
	for (size_t i = 0, ilen = players->size(); i < ilen; ++i) {
		if (players->at(i)->NumberOfCharacterCards() == 2)
			game->GetStateManager()->ChangeState(game, dynamic_pointer_cast<GameState>(make_shared<PlayState>()));
		else if (players->at(i)->HasCrown()) {
			HandleTurn(players->at(i), game);
			if (i == 0)
				HandleTurn(players->at(1), game);
			else
				HandleTurn(players->at(0), game);
		}
	}
}

void PickCardState::HandleTurn(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	player->GetClient()->writeline("Pick a card to remove from deck:");
	PickCard(player, game);
	player->GetClient()->writeline("Pick the card you want to play with:");
	CharacterCard card = PickCard(player, game);
	player->AddCharacterCard(card);
}

CharacterCard PickCardState::PickCard(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	shared_ptr<CardStack<CharacterCard>> characterCards = game->GetCharacterCards();
	for (size_t i = 0, ilen = characterCards->Size(); i < ilen; ++i)
		player->GetClient()->writeline("  " + to_string(i) + ". " + characterCards->ShowCardByIndex(i).GetName());
	// Wait fot command callback
	while (!game->HasNextCommand(player)) {}
	// Get next command for current player
	ClientCommand command = game->GetNextCommand(player);
	char choice[] = "X";
	choice[0] = command.get_cmd().back();
	int index = std::atoi(choice) > 0 ? std::atoi(choice) : 0;
	if (index < 0 || index >= characterCards->Size()) {
		// Invalid index entered
		//return NULL;
	}
	else {
		return characterCards->GetCardByIndex(index);
	}
}
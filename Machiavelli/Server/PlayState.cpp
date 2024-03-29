#include "PlayState.h"
#include "Player.h"
#include "CharacterCard.h"
#include "PlayerStateMachine.h"
#include "GameOverState.h"
#include "PickCardState.h"
#include "AssassinState.h"
#include "ThiefState.h"
#include "BishopState.h"
#include "WarlordState.h"
#include "MerchantState.h"
#include "WizardState.h"
#include "ArchitectState.h"
#include "KingState.h"
#include "GameOverState.h"

PlayState::PlayState() 
{
}


PlayState::~PlayState()
{
}

void PlayState::Init(shared_ptr<Game> &game)
{
	auto players = game->GetPlayers();
	for (size_t i = 0, ilen = players->size(); i < ilen; ++i) {
		players->at(i)->GetClient()->writeline("Starting game!");
	}

	//EnableCheatMode(game);
}

void PlayState::EnableCheatMode(shared_ptr<Game> &game)
{
	auto players = game->GetPlayers();
	for (size_t i = 0, ilen = players->size(); i < ilen; ++i) {
		for (int j = 0; j < 6; j++) 
			players->at(i)->Build(game->GetBuildingCards()->GetRandomCard());
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
	while (!game->GetOrderQueue()->empty())
	{
		Game::Character next = game->GetOrderQueue()->front();
		game->GetOrderQueue()->pop();

		if (!game->HasBeenKilled(next))
		{
			switch (next)
			{
			case Game::ASSASSIN:
			{
				shared_ptr<Player> player = HasCharacterCard(Game::ASSASSIN, game);
				if (player) {
					player->GetStateMachine()->ChangeState(player, game, dynamic_pointer_cast<PlayerState>(make_shared<AssassinState>()));
					player->GetStateMachine()->Update(player, game);
				}
				break;
			}
			case Game::THIEF:
			{
				shared_ptr<Player> player = HasCharacterCard(Game::THIEF, game);
				if (player) {
					player->GetStateMachine()->ChangeState(player, game, dynamic_pointer_cast<PlayerState>(make_shared<ThiefState>()));
					player->GetStateMachine()->Update(player, game);
				}
				break;
			}
			case Game::WIZARD:
			{
				shared_ptr<Player> player = HasCharacterCard(Game::WIZARD, game);
				if (player) {
					if (game->IsThiefTarget(next)) StealGold(next, game);
					player->GetStateMachine()->ChangeState(player, game, dynamic_pointer_cast<PlayerState>(make_shared<WizardState>()));
					player->GetStateMachine()->Update(player, game);
				}
				break;
			}
			case Game::KING:
			{
				shared_ptr<Player> player = HasCharacterCard(Game::KING, game);
				if (player) {
					if (game->IsThiefTarget(next)) StealGold(next, game);
					player->GetStateMachine()->ChangeState(player, game, dynamic_pointer_cast<PlayerState>(make_shared<KingState>()));
					player->GetStateMachine()->Update(player, game);
				}
				break;
			}
			case Game::BISHOP:
			{
				shared_ptr<Player> player = HasCharacterCard(Game::BISHOP, game);
				if (player) {
					if (game->IsThiefTarget(next)) StealGold(next, game);
					player->GetStateMachine()->ChangeState(player, game, dynamic_pointer_cast<PlayerState>(make_shared<BishopState>()));
					player->GetStateMachine()->Update(player, game);
				}
				break;
			}
			case Game::MERCHANT:
			{
				shared_ptr<Player> player = HasCharacterCard(Game::MERCHANT, game);
				if (player) {
					if (game->IsThiefTarget(next)) StealGold(next, game);
					player->GetStateMachine()->ChangeState(player, game, dynamic_pointer_cast<PlayerState>(make_shared<MerchantState>()));
					player->GetStateMachine()->Update(player, game);
				}
				break;
			}
			case Game::ARCHITECT:
			{
				shared_ptr<Player> player = HasCharacterCard(Game::ARCHITECT, game);
				if (player) {
					if (game->IsThiefTarget(next)) StealGold(next, game);
					player->GetStateMachine()->ChangeState(player, game, dynamic_pointer_cast<PlayerState>(make_shared<ArchitectState>()));
					player->GetStateMachine()->Update(player, game);
				}
				break;
			}
			case Game::WARLORD:
			{
				shared_ptr<Player> player = HasCharacterCard(Game::WARLORD, game);
				if (player) {
					if (game->IsThiefTarget(next)) StealGold(next, game);
					player->GetStateMachine()->ChangeState(player, game, dynamic_pointer_cast<PlayerState>(make_shared<WarlordState>()));
					player->GetStateMachine()->Update(player, game);
				}
				break;
			}
			}
		}
	}
	// Check if game is over
	bool finished = false;

	auto players = game->GetPlayers();
	for (size_t i = 0, ilen = players->size(); i < ilen; ++i) {
		if (players->at(i)->GetBuildings()->Size() >= 8)
			finished = true;
	}

	if (finished)
		game->GetStateManager()->ChangeState(game, dynamic_pointer_cast<GameState>(make_shared<GameOverState>()));
	else
		game->GetStateManager()->ChangeState(game, dynamic_pointer_cast<GameState>(make_shared<PickCardState>()));
}

shared_ptr<Player> PlayState::HasCharacterCard(Game::Character character, shared_ptr<Game> &game)
{
	auto players = game->GetPlayers();
	for (size_t i = 0, ilen = players->size(); i < ilen; ++i) {
		shared_ptr<CardStack<CharacterCard>> cards = players->at(i)->GetCharacterCards();
		std::map<Game::Character, std::string>::iterator it = game->GetCharacterMap()->find(character);
		for (size_t c = 0, clen = cards->Size(); c < clen; ++c) {
			if (cards->ShowCardByIndex(c).GetName() == (*it).second) {
				// Remove player card from deck
				//players->at(i)->GetCharacterCards()->EraseCardByIndex(c);
				// Return player
				return players->at(i);
			}
		}
	}
	return nullptr;
}

void PlayState::StealGold(Game::Character character, shared_ptr<Game> &game)
{
	shared_ptr<Player> thief = HasCharacterCard(Game::THIEF, game);
	shared_ptr<Player> victim = HasCharacterCard(character, game);
	int stolenGold = victim->GetGoldAmount();
	string victimName = game->GetCharacterMap()->find(character)->second;
	victim->RemoveGold(stolenGold);
	victim->GetClient()->writeline("A thief has stolen all your gold!");
	thief->AddGold(stolenGold);
	thief->GetClient()->writeline("You have stolen " + to_string(stolenGold) + " gold from the " + victimName + "!");
}

void PlayState::Attack(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}
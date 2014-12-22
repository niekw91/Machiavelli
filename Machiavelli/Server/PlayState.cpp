#include "PlayState.h"
#include "Player.h"
#include "CharacterCard.h"
#include "PlayerStateMachine.h"
#include "AssassinState.h"
#include "ThiefState.h"
#include "BishopState.h"
#include "WarlordState.h"
#include "MerchantState.h"
#include "WizardState.h"
#include "ArchitectState.h"
#include "KingState.h"

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
		players->at(i)->GetClient()->write("Starting game!\n");
	}
	
	GenerateOrder();
	GenerateMap();
}

void PlayState::Cleanup(shared_ptr<Game> &game)
{

}

void PlayState::HandleEvents(shared_ptr<Game> &game)
{

}

void PlayState::Update(shared_ptr<Game> &game)
{
	while (!_orderQueue.empty())
	{
		Character next = _orderQueue.front();
		_orderQueue.pop();

		switch (next)
		{
		case ASSASSIN:
		{
			shared_ptr<Player> player = HasCharacterCard(ASSASSIN, game);
			if (player) {
				player->GetStateMachine()->ChangeState(player, dynamic_pointer_cast<PlayerState>(make_shared<AssassinState>()));
				player->GetStateMachine()->Update(player);
			}
			break;
		}
		case THIEF:
		{
			shared_ptr<Player> player = HasCharacterCard(THIEF, game);
			if (player) {
				player->GetStateMachine()->ChangeState(player, dynamic_pointer_cast<PlayerState>(make_shared<ThiefState>()));
				player->GetStateMachine()->Update(player);
			}
			break;
		}
		case WIZARD:
		{
			shared_ptr<Player> player = HasCharacterCard(WIZARD, game);
			if (player) {
				player->GetStateMachine()->ChangeState(player, dynamic_pointer_cast<PlayerState>(make_shared<WizardState>()));
				player->GetStateMachine()->Update(player);
			}
			break;
		}
		case KING:
		{
			shared_ptr<Player> player = HasCharacterCard(KING, game);
			if (player) {
				player->GetStateMachine()->ChangeState(player, dynamic_pointer_cast<PlayerState>(make_shared<KingState>()));
				player->GetStateMachine()->Update(player);
			}
			break;
		}
		case BISHOP:
		{
			shared_ptr<Player> player = HasCharacterCard(BISHOP, game);
			if (player) {
				player->GetStateMachine()->ChangeState(player, dynamic_pointer_cast<PlayerState>(make_shared<BishopState>()));
				player->GetStateMachine()->Update(player);
			}
			break;
		}
		case MERCHANT:
		{
			shared_ptr<Player> player = HasCharacterCard(MERCHANT, game);
			if (player) {
				player->GetStateMachine()->ChangeState(player, dynamic_pointer_cast<PlayerState>(make_shared<MerchantState>()));
				player->GetStateMachine()->Update(player);
			}
			break;
		}
		case ARCHITECT:
		{
			shared_ptr<Player> player = HasCharacterCard(ARCHITECT, game);
			if (player) {
				player->GetStateMachine()->ChangeState(player, dynamic_pointer_cast<PlayerState>(make_shared<ArchitectState>()));
				player->GetStateMachine()->Update(player);
			}
			break;
		}
		case WARLORD:
		{
			shared_ptr<Player> player = HasCharacterCard(WARLORD, game);
			if (player) {
				player->GetStateMachine()->ChangeState(player, dynamic_pointer_cast<PlayerState>(make_shared<WarlordState>()));
				player->GetStateMachine()->Update(player);
			}
			break;
		}
		}
	}
}

shared_ptr<Player> PlayState::HasCharacterCard(Character character, shared_ptr<Game> &game)
{
	auto players = game->GetPlayers();
	for (size_t i = 0, ilen = players->size(); i < ilen; ++i) {
		shared_ptr<CardStack<CharacterCard>> cards = players->at(i)->GetCharacterCards();
		std::map<Character, std::string>::iterator it = _characterMap.find(character);
		for (size_t c = 0, clen = cards->Size(); c < clen; ++c) {
			if (cards->ShowCardByIndex(c).GetName() == (*it).second) {
				// Remove player card from deck
				players->at(i)->GetCharacterCards()->EraseCardByIndex(c);
				// Return player
				return players->at(i);
			}
		}
	}
	return nullptr;
}

void PlayState::GenerateOrder()
{
	_orderQueue.push(ASSASSIN);
	_orderQueue.push(THIEF);
	_orderQueue.push(WIZARD);
	_orderQueue.push(KING);
	_orderQueue.push(BISHOP);
	_orderQueue.push(MERCHANT);
	_orderQueue.push(ARCHITECT);
	_orderQueue.push(WARLORD);
}

void PlayState::GenerateMap()
{
	_characterMap[ASSASSIN] = "Assassin";
	_characterMap[THIEF] = "Thief";
	_characterMap[WIZARD] = "Wizard";
	_characterMap[KING] = "King";
	_characterMap[BISHOP] = "Bishop";
	_characterMap[MERCHANT] = "Merchant";
	_characterMap[ARCHITECT] = "Architect";
	_characterMap[WARLORD] = "Warlord";
}

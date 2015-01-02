#include "Player.h"
#include "Socket.h"
#include "Game.h"
#include "PlayerStateMachine.h"


Player::Player(shared_ptr<Socket> &client, shared_ptr<Game> &game) {
	_client = client;
	_game = game;
	_hasCrown = false;

	_stateMachine = make_shared<PlayerStateMachine>();
	_buildingCards = make_shared<CardStack<BuildingCard>>();
	_characterCards = make_shared<CardStack<CharacterCard>>();
	_buildings = make_shared<CardStack<BuildingCard>>();
}

Player::~Player()
{
}

void Player::SetCrown(bool crown)
{
	_hasCrown = crown;
}

bool Player::HasCrown()
{
	return _hasCrown;
}

void Player::AddBuildingCard(BuildingCard card)
{
	_buildingCards->AddCard(card);
}

void Player::RemoveBuildingCard(int index)
{
	_buildingCards->EraseCardByIndex(index);
}

BuildingCard Player::GetBuildingCard(int index)
{
	return _buildingCards->GetCardByIndex(index);
}

void Player::AddCharacterCard(CharacterCard card)
{
	_characterCards->AddCard(card);
}

void Player::RemoveCharacterCard(int index)
{
	_characterCards->EraseCardByIndex(index);
}

void Player::Build(BuildingCard card)
{
	_buildings->AddCard(card);
}

void Player::DrawCards(int amount)
{
	for (auto i = 0; i < amount; ++i)
		this->AddBuildingCard(_game->GetBuildingCards()->GetRandomCard());
}

BuildingCard Player::DrawCard()
{
	auto card = _game->GetBuildingCards()->GetRandomCard();
	this->AddBuildingCard(card);
	return card;
}

void Player::SetBuildingCards(shared_ptr<CardStack<BuildingCard>> buildingcards)
{
	_buildingCards = buildingcards;
}
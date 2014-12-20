#include "Player.h"
#include "Socket.h"
#include "Game.h"


Player::Player(shared_ptr<Socket> &client, shared_ptr<Game> &game) {
	_client = client;
	_game = game;
	_hasCrown = false;

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
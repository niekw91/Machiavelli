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

BuildingCard Player::RemoveBuildingCard(int index)
{
	return _buildingCards->GetCardByIndex(index);
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

void Player::DestroyByIndex(int index)
{
	_buildings->GetCardByIndex(index);
}

bool Player::HasCharacterCard(std::string name)
{
	for (size_t i = 0, len = _characterCards->Size(); i < len; ++i) {
		if (_characterCards->ShowCardByIndex(i).GetName() == name)
			return true;
	}
	return false;
}

bool Player::HasBuilding(std::string name)
{
	for (size_t i = 0, len = _buildings->Size(); i < len; ++i) {
		if (_buildings->ShowCardByIndex(i).GetName() == name)
			return true;
	}
	return false;
}
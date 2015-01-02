#include "PlayerState.h"
#include "BuildingCard.h"

#include <string>

void PlayerState::Render(shared_ptr<Player> &player, std::string character)
{
	player->GetClient()->writeline("You are the: " + character);
	player->GetClient()->writeline("Gold: " + std::to_string(player->GetGoldAmount()));

	shared_ptr<CardStack<BuildingCard>> buildings = player->GetBuildings();

	player->GetClient()->writeline("\r\nBuildings:");
	for (size_t i = 0, blen = buildings->Size(); i < blen; ++i) {
		std::string name = buildings->ShowCardByIndex(i).GetName();
		std::string color = std::to_string(buildings->ShowCardByIndex(i).GetColor());
		std::string value = std::to_string(buildings->ShowCardByIndex(i).GetValue());
		player->GetClient()->writeline("  - " + name + "(" + color + "," + value + ")");
	}

	shared_ptr<CardStack<BuildingCard>> buildingCards = player->GetBuildingCards();

	player->GetClient()->writeline("\r\nCards in hand:");
	for (size_t i = 0, blen = buildingCards->Size(); i < blen; ++i) {
		std::string name = buildingCards->ShowCardByIndex(i).GetName();
		std::string color = std::to_string(buildingCards->ShowCardByIndex(i).GetColor());
		std::string value = std::to_string(buildingCards->ShowCardByIndex(i).GetValue());
		player->GetClient()->writeline("  - " + name + "(" + color + "," + value + ")");
	}
}

void PlayerState::ResetChoices()
{
	_basicChoices.push_back(" Show opponent buildings and gold");
	_basicChoices.push_back(" Take 2 gold pieces");
	_basicChoices.push_back(" Take 2 building cards and put 1 away");
	_basicChoices.push_back(" Use character ability");
	_basicChoices.push_back(" End turn");
}

void PlayerState::RenderChoices(shared_ptr<Player> &player)
{
	player->GetClient()->writeline("\r\nMake your choice:");

	//std::map<int, std::string>::iterator it;
	//for (it = _basicChoices.begin(); it != _basicChoices.end(); it++) {
	//	player->GetClient()->writeline("[" + std::to_string(it->first) + "]" + it->second);
	//}

	for (int i = 0; i < _basicChoices.size(); i++) {
		player->GetClient()->writeline("[" + std::to_string(i) + "]" + _basicChoices.at(i));
	}
}

void PlayerState::RemoveChoice(int index)
{
	_basicChoices.erase(_basicChoices.begin() + index);
}

int PlayerState::HandleChoice(shared_ptr<Player> &player, shared_ptr<Game> &game, int range)
{
	// Wait for command callback
	while (!game->HasNextCommand(player)) {}
	// Get next command for current player
	ClientCommand command = game->GetNextCommand(player);
	char choice[] = "X";
	choice[0] = command.get_cmd().back();
	int index = std::atoi(choice) > 0 ? std::atoi(choice) : 0;
	if (index < 0 || index > range) {
		// Invalid index entered
		return -1;
	}
	else {
		return index;
	}
}

void PlayerState::HandleTurn(shared_ptr<Player> &player, shared_ptr<Game> &game, int choice)
{
	switch (choice)
	{
	case 0: // Look at opponent cards
		LookAtOpponent(player, game);
		break;
	case 1: // Take 2 gold
		TakeGold(player, game, 2);
		break;
	case 2: // Take 2 building cards
		TakeBuildingCards(player, game, 2);
		break;
	case 3: // Use ability
		UseAbility(player, game);
		break;
	default:
		break;
	}

	RemoveChoice(choice);
}

void PlayerState::LookAtOpponent(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	// Determine opponent
	shared_ptr<Player> opponent = game->GetOpponent(player);

	// Show opponent information
	player->GetClient()->writeline("Opponent:");
	player->GetClient()->writeline("Gold: " + std::to_string(opponent->GetGoldAmount()));

	shared_ptr<CardStack<BuildingCard>> buildings = opponent->GetBuildings();

	player->GetClient()->writeline("\r\nBuildings:");
	for (size_t i = 0, blen = buildings->Size(); i < blen; ++i) {
		std::string name = buildings->ShowCardByIndex(i).GetName();
		std::string color = std::to_string(buildings->ShowCardByIndex(i).GetColor());
		std::string value = std::to_string(buildings->ShowCardByIndex(i).GetValue());
		player->GetClient()->writeline(std::to_string(i) + " - " + name + "(" + color + "," + value + ")");
	}
}

void PlayerState::TakeGold(shared_ptr<Player> &player, shared_ptr<Game> &game, int amount)
{
	int gold = game->RemoveGold(amount);
	if (gold != -1) {
		player->AddGold(gold);
		player->GetClient()->writeline("You received " + std::to_string(gold) + " gold");
	}
}

void PlayerState::TakeBuildingCards(shared_ptr<Player> &player, shared_ptr<Game> &game, int amount)
{
	for (int i = 0; i < amount; i++)
		player->AddBuildingCard(game->GetBuildingCards()->GetRandomCard());
}
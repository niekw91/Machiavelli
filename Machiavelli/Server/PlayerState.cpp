#include "PlayerState.h"
#include "BuildingCard.h"

#include <string>

void PlayerState::Render(shared_ptr<Player> &player, std::string character)
{
	player->GetClient()->writeline("You are the: " + character);
	player->GetClient()->writeline("Gold: " + std::to_string(player->GetGoldAmount()));

	shared_ptr<CardStack<BuildingCard>> buildings = player->GetBuildings();

	player->GetClient()->writeline("Buildings:");
	for (size_t i = 0, blen = buildings->Size(); i < blen; ++i) {
		std::string name = buildings->ShowCardByIndex(i).GetName();
		std::string color = std::to_string(buildings->ShowCardByIndex(i).GetColor());
		std::string value = std::to_string(buildings->ShowCardByIndex(i).GetValue());
		player->GetClient()->writeline(name + "(" + color + "," + value + ")");
	}

	shared_ptr<CardStack<BuildingCard>> buildingCards = player->GetBuildingCards();

	player->GetClient()->writeline("Cards in hand:");
	for (size_t i = 0, blen = buildingCards->Size(); i < blen; ++i) {
		std::string name = buildingCards->ShowCardByIndex(i).GetName();
		std::string color = std::to_string(buildingCards->ShowCardByIndex(i).GetColor());
		std::string value = std::to_string(buildingCards->ShowCardByIndex(i).GetValue());
		player->GetClient()->writeline(name + "(" + color + "," + value + ")");
	}

	RenderChoices(player);
}

void PlayerState::RenderChoices(shared_ptr<Player> &player)
{
	player->GetClient()->writeline("Make your choice:");
	player->GetClient()->writeline("[0] Show opponent buildings and gold");
	player->GetClient()->writeline("[1] Take 2 gold pieces");
	player->GetClient()->writeline("[2] Take 2 building cards and put 1 away");
	player->GetClient()->writeline("[3] Use character ability");
	player->GetClient()->writeline("[4] End turn");
}

int PlayerState::HandleChoice(shared_ptr<Player> &player, shared_ptr<Game> &game, int range)
{
	// Wait fot command callback
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
}

void PlayerState::LookAtOpponent(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void PlayerState::TakeGold(shared_ptr<Player> &player, shared_ptr<Game> &game, int amount)
{
	int gold = game->RemoveGold(amount);
	if (gold != -1)
		player->AddGold(gold);
}

void PlayerState::TakeBuildingCards(shared_ptr<Player> &player, shared_ptr<Game> &game, int amount)
{
	for (size_t i = 0; i < amount; i++)
		player->AddBuildingCard(game->GetBuildingCards()->GetRandomCard());
}
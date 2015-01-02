#include "PlayerState.h"
#include "BuildingCard.h"

#include <string>

void PlayerState::Render(shared_ptr<Player> &player, std::string character)
{
	player->GetClient()->writeline("You are the: " + character);
	player->GetClient()->writeline("Gold: " + std::to_string(player->GetGoldAmount()));

	RenderBuildings(player);
	RenderCardsInHand(player);
}

void PlayerState::RenderBuildings(shared_ptr<Player> &player)
{
	shared_ptr<CardStack<BuildingCard>> buildings = player->GetBuildings();

	player->GetClient()->writeline("\r\nBuildings:");
	for (size_t i = 0, blen = buildings->Size(); i < blen; ++i) {
		std::string name = buildings->ShowCardByIndex(i).GetName();
		std::string color = std::to_string(buildings->ShowCardByIndex(i).GetColor());
		std::string value = std::to_string(buildings->ShowCardByIndex(i).GetValue());
		player->GetClient()->writeline("  - " + name + "(" + color + "," + value + ")");
	}
}

void PlayerState::RenderCardsInHand(shared_ptr<Player> &player)
{
	shared_ptr<CardStack<BuildingCard>> buildingCards = player->GetBuildingCards();

	player->GetClient()->writeline("\r\nCards in hand:");
	for (size_t i = 0, blen = buildingCards->Size(); i < blen; ++i) {
		std::string name = buildingCards->ShowCardByIndex(i).GetName();
		std::string color = std::to_string(buildingCards->ShowCardByIndex(i).GetColor());
		std::string value = std::to_string(buildingCards->ShowCardByIndex(i).GetValue());
		player->GetClient()->writeline("  - " + name + "(" + color + "," + value + ")");
	}
}

void PlayerState::ResetChoices(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	_basicChoices.push_back(Choice(" Show opponent buildings and gold", (function<void()>)[&] { 
		LookAtOpponent(player, game); 
	}));
	_basicChoices.push_back(Choice(" Take 2 gold pieces", (function<void()>)[&] { 
		TakeGold(player, game, 2);
	}));
	_basicChoices.push_back(Choice(" Take 2 building cards and put 1 away", (function<void()>)[&] { 
		TakeBuildingCards(player, game, 2);
	}));
	_basicChoices.push_back(Choice(" Use character ability", (function<void()>)[&] { 
		UseAbility(player, game);
	}));
	_basicChoices.push_back(Choice(" End turn", (function<void()>)[&] { 
		LookAtOpponent(player, game); 
	}));
}

void PlayerState::RenderChoices(shared_ptr<Player> &player)
{
	player->GetClient()->writeline("\r\nMake your choice:");

	for (size_t i = 0; i < _basicChoices.size(); i++) {
		player->GetClient()->writeline("[" + std::to_string(i) + "]" + _basicChoices.at(i).GetText());
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
	_basicChoices.at(choice).doAction();
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
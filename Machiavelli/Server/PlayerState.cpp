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
		player->GetClient()->writeline(std::to_string(i) + " - " + name + "(" + color + "," + value + ")");
	}
}

void PlayerState::ResetChoices(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	_basicChoices.push_back(Option(" Show opponent buildings and gold", true, (function<void()>)[&] { 
		LookAtOpponent(player, game); 
	}));
	_basicChoices.push_back(Option(" Take 2 gold pieces", false, (function<void()>)[&] {
		TakeGold(player, game, 2);
	}));
	_basicChoices.push_back(Option(" Take 2 building cards and put 1 away", false, (function<void()>)[&] {
		TakeBuildingCards(player, game, 2);
	}));
	_basicChoices.push_back(Option(" Use character ability", false, (function<void()>)[&] {
		UseAbility(player, game);
	}));
	_basicChoices.push_back(Option(" Build building", false, (function<void()>)[&] {
		Build(player, game);
	}));
	_basicChoices.push_back(Option(" End turn", true, (function<void()>)[&] {
		_endTurn = true;
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
	if (!_basicChoices.at(choice).isPermanent()) {
		RemoveChoice(choice);
		for (size_t i = 0, ilen = _basicChoices.size(); i < ilen; ++i) {
			if (!_basicChoices.at(i).isPermanent())
				RemoveChoice(i);
		}
	}
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

void PlayerState::Build(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	RenderCardsInHand(player);

	player->GetClient()->writeline("\nWhat building do you want to build?");

	int choice = -1;
	do {
		choice = HandleChoice(player, game, player->GetBuildingCards()->Size() - 1);
	} while (choice == -1);

	BuildingCard card = player->GetBuildingCard(choice);
	if (player->GetGoldAmount() >= card.GetValue()) {
		player->RemoveGold(card.GetValue());
		game->AddGold(card.GetValue());
		player->Build(card);
		player->GetClient()->writeline("Successfully built " + card.GetName());
	}
	else {
		player->AddBuildingCard(card);
		player->GetClient()->writeline("Not enough gold available to build " + card.GetName());
	}
}
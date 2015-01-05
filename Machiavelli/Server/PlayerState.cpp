#include "PlayerState.h"
#include "BuildingCard.h"

#include <string>

void PlayerState::Render(shared_ptr<Player> &player, std::string character)
{
	player->GetClient()->writeline("You are the: " + character);
	player->GetClient()->writeline("Gold: " + std::to_string(player->GetGoldAmount()));

	player->GetClient()->writeline("\r\nBuildings:");
	RenderBuildings(player);

	player->GetClient()->writeline("\r\nCards in hand:");
	RenderCardsInHand(player);
}

void PlayerState::RenderBuildings(shared_ptr<Player> &player)
{
	shared_ptr<CardStack<BuildingCard>> buildings = player->GetBuildings();

	for (size_t i = 0, blen = buildings->Size(); i < blen; ++i) {
		std::string name = buildings->ShowCardByIndex(i).GetName();
		std::string color = GetColor(buildings->ShowCardByIndex(i).GetColor());
		std::string value = std::to_string(buildings->ShowCardByIndex(i).GetValue());
		player->GetClient()->writeline("  " + to_string(i) + ". " + name + " (" + color + ", " + value + ")");
	}
}

void PlayerState::RenderCardsInHand(shared_ptr<Player> &player)
{
	shared_ptr<CardStack<BuildingCard>> buildingCards = player->GetBuildingCards();

	for (size_t i = 0, blen = buildingCards->Size(); i < blen; ++i) {
		std::string name = buildingCards->ShowCardByIndex(i).GetName();
		std::string color = GetColor(buildingCards->ShowCardByIndex(i).GetColor());
		std::string value = std::to_string(buildingCards->ShowCardByIndex(i).GetValue());
		player->GetClient()->writeline("  " + to_string(i) + ". " + name + " (" + color + ", " + value + ")");
	}
}

void PlayerState::ResetChoices(shared_ptr<Player> &player, shared_ptr<Game> &game, string character)
{

	_basicChoices.push_back(Option("show", " Show opponent buildings and gold", true, (function<void()>)[&] {
		LookAtOpponent(player, game);
	}));
	_basicChoices.push_back(Option("gold", " Take 2 gold pieces", false, (function<void()>)[&] {
		TakeGold(player, game, 2);
	}));
	if (character == "Architect")
		_basicChoices.push_back(Option("card", " Take 2 building cards", false, (function<void()>)[&] {
			TakeBuildingCards(player, game, 2);

			// Show building cards
			RenderCardsInHand(player);
		}));
	else
		_basicChoices.push_back(Option("card", " Take 2 building cards and put 1 away", false, (function<void()>)[&] {
			// Draw 2 building cards
			TakeBuildingCards(player, game, 2);

			if (player->HasBuilding("Library"))
				player->GetClient()->writeline("\nYou have the library building and therefor may keep both cards");
			else
			{
				// Show building cards
				RenderCardsInHand(player);

				player->GetClient()->writeline("\nWhat card do you want to put away?");

				// Choose building card to be removed
				int choice = -1;
				do {
					choice = HandleChoice(player, game, player->GetBuildingCards()->Size());
				} while (choice == -1);

				BuildingCard card = player->RemoveBuildingCard(choice);
				game->AddBuildingCard(card); // Add back to building card stack
			}
		}));
	_basicChoices.push_back(Option("ability", " Use character ability", false, (function<void()>)[&] {
		UseAbility(player, game);
	}));
	for (int i = 0, ilen = character == "Architect" ? 3 : 1; i < ilen; ++i)
		_basicChoices.push_back(Option("build", " Build building", false, (function<void()>)[&] {
			Build(player, game);
		}));
	if (player->HasBuilding("Laboratory")) {
		_basicChoices.push_back(Option("laboratory", " Trade building card for 1 gold coin [Laboratory]", false, (function<void()>)[&] {
			// Show building cards
			RenderCardsInHand(player);

			player->GetClient()->writeline("\nWhat card do you want to put away?");

			// Choose building card to be removed
			int choice = -1;
			do {
				choice = HandleChoice(player, game, player->GetBuildingCards()->Size());
			} while (choice == -1);

			BuildingCard card = player->RemoveBuildingCard(choice);
			game->AddBuildingCard(card); // Add back to building card stack
			TakeGold(player, game, 1);			
		}));
	}
	if (player->HasBuilding("Workshop")) {
		_basicChoices.push_back(Option("workshop", " Pay 3 gold coins and receive 2 building cards [Workshop]", false, (function<void()>)[&] {
			if (player->GetGoldAmount() >= 3) {
				player->RemoveGold(3);
				game->AddGold(3);

				TakeBuildingCards(player, game, 2);
			}
		}));
	}
	_basicChoices.push_back(Option("done", " End turn", true, (function<void()>)[&] {
		_endTurn = true;
	}));
}

void PlayerState::ResetChoices(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	ResetChoices(player, game, "");
}

void PlayerState::RenderChoices(shared_ptr<Player> &player)
{
	player->GetClient()->writeline("\r\nMake your choice:");

	for (size_t i = 0; i < _basicChoices.size(); i++) {
		player->GetClient()->writeline("  " + to_string(i) + ". " + _basicChoices.at(i).GetText());
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
		if (_basicChoices.at(choice).GetKey() == "gold" || _basicChoices.at(choice).GetKey() == "card") {
			RemoveChoice(1);
			RemoveChoice(1);
		}
		else
			RemoveChoice(choice);
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
		std::string color = GetColor(buildings->ShowCardByIndex(i).GetColor());
		std::string value = std::to_string(buildings->ShowCardByIndex(i).GetValue());
		player->GetClient()->writeline("  " + to_string(i) + ". " + name + " (" + color + ", " + value + " gold)");
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

std::string PlayerState::GetColor(int c)
{
	std::string color;

	switch (c) 
	{
	case Game::BLUE:
		color = "Blue";
		break;
	case Game::RED:
		color = "Red";
		break;
	case Game::PURPLE:
		color = "Purple";
		break;
	case Game::YELLOW:
		color = "Yellow";
		break;
	case Game::GREEN:
		color = "Green";
		break;
	default:
		break;
	}

	return color;
}
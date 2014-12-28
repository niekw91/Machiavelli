#pragma once
#include "Player.h"
#include "PlayerStateMachine.h"
#include "Socket.h"
#include "BuildingCard.h"

#include <memory>
#include <string>

class PlayerState
{
public:
	PlayerState() { }
	~PlayerState() { }

	virtual void Init(shared_ptr<Player> &player) = 0;
	virtual void Cleanup(shared_ptr<Player> &player) = 0;

	virtual void HandleEvents(shared_ptr<Player> &player) = 0;
	virtual void Update(shared_ptr<Player> &player) = 0;

	void Write(shared_ptr<Player> &player, std::string character)
	{
		player->GetClient()->write("You are the: " + character + "\n");
		player->GetClient()->write("Gold: " + std::to_string(player->GetGoldAmount()) + "\n");

		shared_ptr<CardStack<BuildingCard>> buildings = player->GetBuildings();

		player->GetClient()->write("Buildings:\n");
		for (size_t i = 0, blen = buildings->Size(); i < blen; ++i) {
			std::string name = buildings->ShowCardByIndex(i).GetName();
			std::string color = std::to_string(buildings->ShowCardByIndex(i).GetColor());
			std::string value = std::to_string(buildings->ShowCardByIndex(i).GetValue());
			player->GetClient()->write(name + "(" + color + "," + value + ")\n");
		}

		shared_ptr<CardStack<BuildingCard>> buildingCards = player->GetBuildingCards();

		player->GetClient()->write("Cards in hand:");
		for (size_t i = 0, blen = buildingCards->Size(); i < blen; ++i) {
			std::string name = buildingCards->ShowCardByIndex(i).GetName();
			std::string color = std::to_string(buildingCards->ShowCardByIndex(i).GetColor());
			std::string value = std::to_string(buildingCards->ShowCardByIndex(i).GetValue());
			player->GetClient()->write(name + "(" + color + "," + value + ")\n");
		}

		player->GetClient()->write("Make your choice:\n");
		player->GetClient()->write("[0] Show opponent buildings and gold\n");
		player->GetClient()->write("[1] Take 2 gold pieces\n");
		player->GetClient()->write("[2] Take 2 building cards and put 1 away\n");
		player->GetClient()->write("[3] Use the character ability of the " + character + "\n");

	}
};


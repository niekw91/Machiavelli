#include "BishopState.h"


BishopState::BishopState()
{
}


BishopState::~BishopState()
{
}

void BishopState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	// Receive gold for player color buildings
	int playercolor = Game::Color::BLUE;
	int playercolorbuildings = 0;
	auto buildings = player->GetBuildings();

	for (auto i = 0, ilen = buildings->Size(); i < ilen; ++i) {
		if (buildings->ShowCardByIndex(i).GetColor() == playercolor)
			++playercolorbuildings;
	}
	if (playercolorbuildings > 0)
		player->AddGold(playercolorbuildings);
	else {
		player->GetClient()->writeline("You do not own any " + GetColor(playercolor) + " buildings and therefore receive no gold");
	}
	if (player->HasBuilding("School of Wizards")) {
		int gold = 1;
		player->AddGold(gold);
		player->GetClient()->writeline("You receive 1 gold coin for the School of Wizards, " + to_string(gold) + " gold received!");
	}
}

void BishopState::Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void BishopState::HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void BishopState::Update(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	Render(player, "Bishop");
	ResetChoices(player, game);
	_endTurn = false;
	int choice = -1;
	while (!_endTurn) {
		do {
			RenderChoices(player);
			choice = HandleChoice(player, game, GetNumberOfChoices() - 1);
		} while (choice == -1);
		HandleTurn(player, game, choice);
	}
}

void BishopState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}
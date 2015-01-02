#include "KingState.h"


KingState::KingState()
{
}


KingState::~KingState()
{
}

void KingState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	game->GetOpponent(player)->SetCrown(false);
	player->SetCrown(true);
	int goldForBuildings = 0;
	auto buildings = player->GetBuildings();
	for (auto i = 0, ilen = buildings->Size(); i < ilen; ++i) {
		if (buildings->GetCardByIndex(i).GetColor() == Game::Color::YELLOW)
			++goldForBuildings;
	}
	if (goldForBuildings > 0)
		player->AddGold(goldForBuildings);
}

void KingState::Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void KingState::HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void KingState::Update(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	Render(player, "King");
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

void KingState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	player->GetClient()->writeline("King Character Traits:");
	player->GetClient()->writeline("  - A king receives 1 gold piece for every gold building he has built.");
	player->GetClient()->writeline("  - A King also gets to start at the beginning of a round.");
}
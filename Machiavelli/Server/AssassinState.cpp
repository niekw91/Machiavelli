#include "AssassinState.h"
#include "GameStateManager.h"

AssassinState::AssassinState()
{
}


AssassinState::~AssassinState()
{
}

void AssassinState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void AssassinState::Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void AssassinState::HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void AssassinState::Update(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	Render(player, "Assassin");
	int choice = -1;
	while (choice != 4) {
		do {
			choice = HandleChoice(player, game, 4);
		} while (choice == -1);
		HandleTurn(player, game, choice);
	}
}

void AssassinState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	player->GetClient()->write("\nYou are allowed to assinate one of the following players:\n");
	player->GetClient()->write("[0] Thief\n");
	player->GetClient()->write("[1] Wizard\n");
	player->GetClient()->write("[2] King\n");
	player->GetClient()->write("[3] Bishop\n");
	player->GetClient()->write("[4] Merchant\n");
	player->GetClient()->write("[5] Architect\n");
	player->GetClient()->write("[6] Warlord\n");

	int choice = -1;
	do {
		choice = HandleChoice(player, game, 6);
	} while (choice == -1);

	Game::Character character;
	switch (choice)
	{
	case 0: character = Game::THIEF; break;
	case 1: character = Game::WIZARD; break;
	case 2: character = Game::KING; break;
	case 3: character = Game::BISHOP; break;
	case 4: character = Game::MERCHANT; break;
	case 5: character = Game::ARCHITECT; break;
	case 6: character = Game::WARLORD; break;
	}

	game->KillCharacter(character);
}
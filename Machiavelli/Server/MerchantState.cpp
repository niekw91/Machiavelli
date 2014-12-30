#include "MerchantState.h"


MerchantState::MerchantState()
{
}


MerchantState::~MerchantState()
{
}

void MerchantState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void MerchantState::Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void MerchantState::HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void MerchantState::Update(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	Render(player, "Merchant");
	int choice = -1;
	while (choice != 4) {
		do {
			choice = HandleChoice(player, game, 4);
		} while (choice == -1);
		HandleTurn(player, game, choice);
	}
}

void MerchantState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

#include "GameOverState.h"
#include "Player.h"
#include <set>


GameOverState::GameOverState()
{
}


GameOverState::~GameOverState()
{
}

void GameOverState::Init(shared_ptr<Game> &game)
{
	auto players = game->GetPlayers();

	for (size_t i = 0, ilen = players->size(); i < ilen; ++i) {
		// Check if player has Dragongate or University buildings
		auto buildings = players->at(i)->GetBuildings();
		for (size_t k = 0, klen = buildings->Size(); k < klen; ++k) {
			if (buildings->ShowCardByIndex(k).GetName() == "Dragongate") {
				buildings->EraseCardByIndex(k);
				players->at(i)->AddPoints(8);
			}
			if (buildings->ShowCardByIndex(k).GetName() == "University") {
				buildings->EraseCardByIndex(k);
				players->at(i)->AddPoints(8);
			}
		}

		// Give player points for built buildings
		players->at(i)->AddPoints(players->at(i)->GetBuildings()->Size());

		// Give player 3 points if 5 different colored buildings are built
		bool hasCourtOfMiracles = false;
		int numberOfColors = 0;
		set<int> colors;
		for (size_t j = 0, jlen = buildings->Size(); j < jlen; ++j) {
			if (buildings->ShowCardByIndex(j).GetName() == "Court of Miracles")
				hasCourtOfMiracles = true;
			for (size_t k = 0, klen = colors.size(); k < klen; ++k) {
				if (colors.find(buildings->GetCardByIndex(j).GetColor()) == colors.end()) {
					colors.insert(buildings->GetCardByIndex(j).GetColor());
					++numberOfColors;
				}
			}
		}

		if (numberOfColors >= 5 || numberOfColors >= 4 && hasCourtOfMiracles)
			players->at(i)->AddPoints(3);

		// Give player that has 8 buildings 4 points
		if (players->at(i)->GetBuildings()->Size() >= 8)
			players->at(i)->AddPoints(4);
	}
}

void GameOverState::Cleanup(shared_ptr<Game> &game)
{

}

void GameOverState::HandleEvents(shared_ptr<Game> &game)
{

}

void GameOverState::Update(shared_ptr<Game> &game)
{
	auto player1 = game->GetPlayers()->at(0);
	auto player2 = game->GetPlayers()->at(1);

	int player1points = player1->GetScore();
	int player2points = player2->GetScore();

	// Show scores
	player1->GetClient()->writeline("You scored " + to_string(player1points) + " points.");
	player1->GetClient()->writeline("Your opponent has " + to_string(player1points) + " points.");

	player2->GetClient()->writeline("You scored " + to_string(player2points) + " points.");
	player2->GetClient()->writeline("Your opponent has " + to_string(player2points) + " points.");

	// Determine winner
	int winner = -1;
	if (player1points != player2points)
		winner = player1points > player2points ? 0 : 1;
	else {
		player1points = 0;
		player2points = 0;
		auto buildings = player1->GetBuildings();
		for (size_t j = 0, jlen = buildings->Size(); j < jlen; ++j) {
			player1points += buildings->ShowCardByIndex(j).GetValue();
		}
		buildings = player2->GetBuildings();
		for (size_t j = 0, jlen = buildings->Size(); j < jlen; ++j) {
			player2points += buildings->ShowCardByIndex(j).GetValue();
		}
		if (player1points != player2points)
			winner = player1points > player2points ? 0 : 1;
	}

	switch (winner) {
	case -1:
		player1->GetClient()->writeline("\r\nCongratulations it's a tie!");
		player2->GetClient()->writeline("\r\nCongratulations it's a tie!");
		break;
	case 0:
		player1->GetClient()->writeline("\r\nCongratulations you've won!");
		break;
	case 1:
		player2->GetClient()->writeline("\r\nCongratulations you've won!");
		break;
	}
}

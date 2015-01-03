#include "CardFactory.h"
#include "Card.h"
#include "CharacterCard.h"
#include "GameObject.h"
#include "BuildingCard.h"
#include "Game.h"

#include <iostream>
#include <fstream>
#include <sstream>

CardFactory::CardFactory()
{
	_buildingCards = make_shared<CardStack<BuildingCard>>();
	_characterCards = make_shared<CardStack<CharacterCard>>();
}


CardFactory::~CardFactory()
{
}

void CardFactory::CreateCharacterCardsFromFile(std::string filename, std::shared_ptr<Game> &game)
{
	std::ifstream input_file(filename); // stack-based file object; deze constructie opent de file voor lezen
	std::string line;

	while (getline(input_file, line)) { // getline() geeft false zodra end-of-file is bereikt
		std::vector<std::string> v = Split(line, ';');

		std::vector<std::string> description = std::vector<std::string>();

		if (v.size() == 4) {
			description.push_back(v.at(3));
		}
		else if (v.size() == 5) {
			description.push_back(v.at(3));
			description.push_back(v.at(4));
		}
		CharacterCard card = CharacterCard(std::stoi(v.at(0)), v.at(1), std::stoi(v.at(2)), description);
		//game->AddCharacterCard(card);
		_characterCards->AddCard(card);
	}
}

void CardFactory::CreateBuildingCardsFromFile(std::string filename, std::shared_ptr<Game> &game)
{
	std::ifstream input_file(filename); // stack-based file object; deze constructie opent de file voor lezen
	std::string line;

	while (getline(input_file, line)) { // getline() geeft false zodra end-of-file is bereikt
		std::vector<std::string> v = Split(line, ';');

		std::vector<std::string> description = std::vector<std::string>();

		if (v.size() == 5) {
			description.push_back(v.at(4));
			BuildingCard card = BuildingCard(std::stoi(v.at(0)), v.at(1), std::stoi(v.at(2)), std::stoi(v.at(3)), description);
			//game->AddBuildingCard(card);
			_buildingCards->AddCard(card);
		}
		else {
			BuildingCard card = BuildingCard(std::stoi(v.at(0)), v.at(1), std::stoi(v.at(2)), std::stoi(v.at(3)));
			//game->AddBuildingCard(card);
			_buildingCards->AddCard(card);
		}
	}
}

std::vector<std::string> CardFactory::Split(const std::string &s, char &delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> CardFactory::Split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	Split(s, delim, elems);
	return elems;
}
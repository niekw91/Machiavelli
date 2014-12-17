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

		for (int i = 0; i < v.size(); i++)
			std::cerr << v.at(i) << "\n";

		if (v.size() == 4) {
			std::vector<std::string> description = std::vector<std::string>();
			description.push_back(v.at(3));
			CharacterCard card = CharacterCard(std::stoi(v.at(0)), v.at(1), std::stoi(v.at(2)), description);
		}
		else if (v.size() == 5) {
			std::vector<std::string> description = std::vector<std::string>();
			description.push_back(v.at(3));
			description.push_back(v.at(4));
			CharacterCard card = CharacterCard(std::stoi(v.at(0)), v.at(1), std::stoi(v.at(2)), description);
		}
	}
}

void CardFactory::CreateBuildingCardsFromFile(std::string filename, std::shared_ptr<Game> &game)
{
	std::ifstream input_file(filename); // stack-based file object; deze constructie opent de file voor lezen
	std::string line;

	while (getline(input_file, line)) { // getline() geeft false zodra end-of-file is bereikt
		std::vector<std::string> v = Split(line, ';');

		for (int i = 0; i < v.size(); i++)
			std::cerr << v.at(i) << "\n";

		if (v.size() == 2) {
			// Create character card
			//CharacterCard card = new CharacterCard
		}
		else if (v.size() == 3) {
			// Create normal building card
		}
		else if (v.size() == 4) {
			// Create special building card
		}
		std::cout << line << '\n'; // getline() haalt de \n wel uit de stream, maar voegt die niet toe
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
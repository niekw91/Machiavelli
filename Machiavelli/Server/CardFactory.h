#pragma once
#include "CardStack.h"
#include <string>
#include <vector>
#include <memory>

class Game;
class CharacterCard;
class BuildingCard;

class CardFactory
{
public:
	CardFactory();
	virtual ~CardFactory();

	void CreateCharacterCardsFromFile(std::string filename, std::shared_ptr<Game> &game);
	void CreateBuildingCardsFromFile(std::string filename, std::shared_ptr<Game> &game);
	shared_ptr<CardStack<CharacterCard>> GetCharacterCards() { return _characterCards; }
	shared_ptr<CardStack<BuildingCard>> GetBuildingCards() { return _buildingCards; }
private:
	std::vector<std::string> Split(const std::string &s, char &delim, std::vector<std::string> &elems);
	std::vector<std::string> Split(const std::string &s, char delim);

	shared_ptr<CardStack<CharacterCard>> _characterCards;
	shared_ptr<CardStack<BuildingCard>> _buildingCards;
};


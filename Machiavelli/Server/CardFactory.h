#pragma once
#include <string>
#include <vector>
#include <memory>

class Game;

class CardFactory
{
public:
	CardFactory();
	virtual ~CardFactory();

	void CreateCharacterCardsFromFile(std::string filename, std::shared_ptr<Game> &game);
	void CreateBuildingCardsFromFile(std::string filename, std::shared_ptr<Game> &game);
private:
	std::vector<std::string> Split(const std::string &s, char &delim, std::vector<std::string> &elems);
	std::vector<std::string> Split(const std::string &s, char delim);
};


#include "BuildingCard.h"


BuildingCard::BuildingCard(int id, string name, int value, int color) : Card(id, name, color)
{
	_value = value;
}

BuildingCard::BuildingCard(int id, string name, int value, int color, vector<string> description) : Card(id, name, color, description)
{
	_value = value;
}

BuildingCard::~BuildingCard()
{
}

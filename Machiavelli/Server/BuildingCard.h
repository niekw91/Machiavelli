#pragma once
#include "Card.h"

#pragma once
#include "Card.h"

#include <string>
#include <vector>

using namespace std;

class BuildingCard :
	public Card
{
public:
	BuildingCard(int id, string name, int value, int color);
	BuildingCard(int id, string name, int value, int color, vector<string> description);
	~BuildingCard();

	int GetValue() { return _value; }

private:
	int _value;
};


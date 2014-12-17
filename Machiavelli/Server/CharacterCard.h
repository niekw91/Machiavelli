#pragma once
#include "Card.h"
#include <string>
#include <vector>

using namespace std;

class CharacterCard :
	public Card
{
public:
	CharacterCard(int id, string name, int color, vector<string> description);
	~CharacterCard();
};
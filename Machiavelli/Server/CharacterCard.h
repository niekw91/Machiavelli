#pragma once
#include "Card.h"
class CharacterCard :
	public Card
{
public:
	CharacterCard(int id, string name, int color, vector<string> description);
	~CharacterCard();
};
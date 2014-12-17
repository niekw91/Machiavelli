#include "Card.h"

Card::Card(int id, string name) : GameObject(name)
{
	_id = id;
}

Card::Card(int id, string name, int color) : GameObject(name)
{
	_id = id;
	_color = color;
}

Card::Card(int id, string name, vector<string> description) : GameObject(name)
{
	_id = id;
	_description = description;
}

Card::Card(int id, string name, int color, vector<string> description) : GameObject(name)
{
	_id = id;
	_color = color;
	_description = description;
}

Card::~Card()
{
}

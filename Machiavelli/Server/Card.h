#pragma once
#include "GameObject.h"
#include <vector>

class Card :
	public GameObject
{
public:
	Card(int id, string name);
	Card(int id, string name, int color);
	Card(int id, string name, vector<string> description);
	Card(int id, string name, int color, vector<string> description);
	~Card();

	int GetId() { return _id; }
	int GetColor() { return _color; }
	vector<string> GetDescription() { return _description; }

private:
	int _id;
	int _color;
	vector<string> _description;
};


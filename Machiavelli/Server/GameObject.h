#pragma once
#include <string>

using namespace std;

class GameObject
{
public:
	GameObject(string name) { _name = name; }
	virtual ~GameObject() {}

	string GetName() { return _name; }

protected:
	string _name;
};
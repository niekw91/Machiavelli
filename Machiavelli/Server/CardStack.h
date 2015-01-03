#pragma once
#include "Random.h"

#include <memory>
#include <vector>

template <class card_type>
class CardStack
{
public:
	CardStack(){}
	~CardStack(){}

	//shared_ptr<card_type> GetNextCard()
	//{
	//	int random = Random::Next(0, _cards.size() - 1);
	//	shared_ptr<card_type> card = _cards.at(random);
	//	_cards.erase(random);
	//	return card;
	//}

	card_type GetCardByIndex(int index)
	{
		card_type card = _cards.at(index);
		EraseCardByIndex(index);
		return card;
	}

	card_type GetRandomCard()
	{
		int index = Random::Next(0, _cards.size() - 1);
		card_type card = _cards.at(index);
		EraseCardByIndex(index);
		return card;
	}

	card_type ShowCardByIndex(int index)
	{
		return _cards.at(index);
	}

	void EraseCardByIndex(int index)
	{
		_cards.erase(_cards.begin() + index);
	}

	void AddCard(card_type card)
	{
		_cards.push_back(card);
	}

	int Size()
	{
		return _cards.size();
	}

	void Clear()
	{
		_cards.clear();
	}

private:
	std::vector<card_type> _cards;
};


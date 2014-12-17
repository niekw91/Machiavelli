#pragma once
#include "Random.h"

#include <memory>
#include <vector>

template <class card_type>
class CardStack
{
public:
	CardStack();
	~CardStack();

	//shared_ptr<card_type> GetNextCard()
	//{
	//	int random = Random::Next(0, _cards.size() - 1);
	//	shared_ptr<card_type> card = _cards.at(random);
	//	_cards.erase(random);
	//	return card;
	//}

	shared_ptr<card_type> GetCardByIndex(int index)
	{
		shared_ptr<card_type> card = _cards.at(index);
		EraseCardByIndex(index);
		return card;
	}

	void EraseCardByIndex(int index)
	{
		_cards.erase(index);
	}

	void AddCard(shared_ptr<card_type> card)
	{
		_cards.push_back(card);
	}

private:
	std::vector<shared_ptr<card_type>> _cards;
};


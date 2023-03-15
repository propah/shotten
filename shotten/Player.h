#pragma once
#include <vector>
#include <iostream>
#include "Card.h"
#include "Option.h"

enum class PlayerNumber {
	ONE,
	TWO
};

class Player
{
private:
	std::vector<Card> hand;
public:
	Player();
	void addCard(Card card);
	void removeCard(Card card);
	void displayHand();
	std::vector<Card> getHand();
	Option<Card> getCard(int number);
};


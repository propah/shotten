#pragma once
#include <vector>
#include <iostream>
#include <memory>
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
	void displayHand() const;
	std::vector<Card> getHand() const;
	Option<Card> getCard(int number) const;
};


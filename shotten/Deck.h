#pragma once
#include "Card.h"
#include "Option.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <random>
#include <memory>

static const int DECK_SIZE = 54;
class Deck
{
private:
	std::vector<Card> cards;
public:
	Deck();
	Option<Card> drawCard();
};


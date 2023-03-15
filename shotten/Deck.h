#pragma once
#include "Card.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <random>
#include <optional>

static const int DECK_SIZE = 54;
class Deck
{
private:
	std::vector<Card> cards;
public:
	Deck();
	std::optional<Card> drawCard();
};


#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Landmark.h"
#include "Card.h"
#include "Deck.h"

static const int BOARD_SIZE = 9;
class Board
{
private:
	std::vector<Landmark> landmarks;

	bool isNumberValid(int number) const;
public:
	Board();
	std::vector<Landmark> getLandmarks() const;
	Landmark getLandMark(int number) const;
	int getSize() const;
	void placeCard(int number, Card card, PlayerNumber player_number);
	void display() const;
};


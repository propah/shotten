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

	bool isNumberValid(int number);
public:
	Board();
	std::vector<Landmark> getLandmarks();
	Landmark getLandMark(int number);
	int getSize();
	void placeCard(int number, Card card, PlayerNumber player_number);
	void display();
};


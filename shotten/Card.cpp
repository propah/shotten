#include "Card.h"


Card::Card(int number, CardColor color) {
	this->number = number;
	this->color = color;
}

int Card::getNumber()
{
	return this->number;
}

CardColor Card::getColor()
{
	return this->color;
}


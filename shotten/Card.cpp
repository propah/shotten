#include "Card.h"


Card::Card(int number, CardColor color) {
	this->number = number;
	this->color = color;
}

int Card::getNumber() const
{
	return this->number;
}

CardColor Card::getColor() const
{
	return this->color;
}


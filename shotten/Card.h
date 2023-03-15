#pragma once
#include <string>
#include <sstream>
#include <vector>
enum class CardColor {
	BLUE,
	RED,
	GREEN,
	BROWN,
	YELLOW,
	PURPLE,
};

static const CardColor AllCardColors[] = { CardColor::BLUE, CardColor::RED, CardColor::GREEN, CardColor::BROWN, CardColor::YELLOW, CardColor::PURPLE };

class Card
{
private:
	int number;
	CardColor color;
public:
	Card(int number, CardColor color);
	int getNumber();
	CardColor getColor();
	friend bool operator==(const Card& card_left, const Card& card_right) {
		return card_left.color == card_right.color && card_left.number == card_right.number;
	}
	friend std::ostream& operator<<(std::ostream& os, const Card& m) {
		std::string color;
		switch (m.color) {
		case CardColor::BLUE:
			color = "B";
			break;
		case CardColor::RED:
			color = "R";
			break;
		case CardColor::GREEN:
			color = "G";
			break;
		case CardColor::BROWN:
			color = "M";
			break;
		case CardColor::YELLOW:
			color = "Y";
			break;
		case CardColor::PURPLE:
			color = "P";
			break;
		}
		os << std::to_string(m.number) << color;
		return os;
	}
};




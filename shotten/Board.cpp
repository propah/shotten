#include "Board.h"

bool Board::isNumberValid(int number)
{
	if (number >= BOARD_SIZE || number < 0) {
		return false;
	}
	return true;
}

Board::Board()
{
	this->landmarks = std::vector<Landmark>();
	for (int i = 0; i < BOARD_SIZE; i++) {
		this->landmarks.push_back(Landmark());
	}
}

std::vector<Landmark> Board::getLandmarks()
{
	return this->landmarks;
}

Landmark Board::getLandMark(int number)
{
	if (!this->isNumberValid(number)) {
		std::cout << "ERROR: Wrong LandMark asked, returning first landmark\n";
		return this->landmarks[0];
	}
	return this->landmarks[number];
}

int Board::getSize()
{
	return static_cast<int>(this->landmarks.size());
}

void Board::placeCard(int number, Card card, PlayerNumber player_number)
{
	if (!this->isNumberValid(number)) {
		std::cout << "ERROR: Wrong LandMark asked, adding player's card to first landmark\n";
		number = 0;
	}
	if (this->landmarks[number].getCards(player_number).size() >= 3) {
		std::cout << "ERROR: Player's landmark number " << number << " is at full capacity";
	}
	else {
		this->landmarks[number].addCard(card, player_number);
	}
}

void Board::display()
{
	std::vector<Card> line1 = std::vector<Card>();
	std::vector<Card> line2 = std::vector<Card>();
	std::vector<Card> line3 = std::vector<Card>();
	PlayerNumber current_player = PlayerNumber::TWO;
	for (Landmark landmark : this->landmarks) {
		auto temp = landmark.getCards(current_player);
		if (temp.size() >= 3) {
			line1.push_back(temp[2]);
		}
		else {
			line1.push_back(Card(0, CardColor::BLUE));
		}
		if (temp.size() >= 2) {
			line2.push_back(temp[1]);
		}
		else {
			line2.push_back(Card(0, CardColor::BLUE));
		}
		if (temp.size() >= 1) {
			line3.push_back(temp[0]);
		}
		else {
			line3.push_back(Card(0, CardColor::BLUE));
		}
	}
	char square = 254;
	for (std::vector<Card> line: { line1, line2, line3 }) {
		for (Card card : line) {
			if (card.getNumber() != 0) {
				std::cout << card << " ";
			}
			else {
				std::cout << ".. ";
			}
		}
		std::cout << "\n";
	}
	for (int i = 0; i < 9; i++) {
		std::cout << square << square << " ";
	}
	std::cout << "\n";
	line1 = std::vector<Card>();
	line2 = std::vector<Card>();
	line3 = std::vector<Card>();
	current_player = PlayerNumber::ONE;
	for (Landmark landmark : this->landmarks) {
		auto temp = landmark.getCards(current_player);
		if (temp.size() >= 3) {
			line1.push_back(temp[2]);
		}
		else {
			line1.push_back(Card(0, CardColor::BLUE));
		}
		if (temp.size() >= 2) {
			line2.push_back(temp[1]);
		}
		else {
			line2.push_back(Card(0, CardColor::BLUE));
		}
		if (temp.size() >= 1) {
			line3.push_back(temp[0]);
		}
		else {
			line3.push_back(Card(0, CardColor::BLUE));
		}
	}
	for (std::vector<Card> line : { line3, line2, line1 }) {
		for (Card card : line) {
			if (card.getNumber() != 0) {
				std::cout << card << " ";
			}
			else {
				std::cout << ".. ";
			}
		}
		std::cout << "\n";
	}
}

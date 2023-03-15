#include "Player.h"

Player::Player()
{
	this->hand = std::vector<Card>();
}

void Player::addCard(Card card)
{
	this->hand.push_back(card);
}

void Player::removeCard(Card card)
{
	for (int i = 0; i < this->hand.size(); i++) {
		if (this->hand[i] == card) {
			this->hand.erase(this->hand.begin()+i);
			return;
		}
	}
	std::cout << "WARNING: Couldn't remove card in player's hand\n";
}

void Player::displayHand()
{
	std::cout << "Your hand: ";
	for (Card card : this->hand) {
		std::cout << card << " ";
	}
	std::cout << "\n";
}

std::vector<Card> Player::getHand()
{
	return this->hand;
}

Option<Card> Player::getCard(int number) {
	if (this->hand.empty()) {
		std::cout << "ERROR: Hand is empty but still requested a card\n";
		return Option<Card>();
	}
	if (number > this->hand.size()) {
		std::cout << "ERROR: Card requested is not in hand";
		return Option<Card>();
	}
	return Option<Card>(&this->hand[number]);
}
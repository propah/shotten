#include "Deck.h"

Deck::Deck()
{
	this->cards = std::vector<Card>();
	auto rd = std::random_device{};
	auto rng = std::default_random_engine{ rd() };
	for (const CardColor color : AllCardColors) {
		for (int i = 1; i <= 9; i++) {
			this->cards.push_back(Card(i, color));
		}
	}
	std::shuffle(this->cards.begin(), this->cards.end(), rng);
}

std::optional<Card> Deck::drawCard()
{
	if (this->cards.empty()) {
		std::cout << "INFO: Deck is empty\n";
		return {};
	}
	Card temp_card = this->cards[this->cards.size()-1];
	this->cards.pop_back();
	return temp_card;
}

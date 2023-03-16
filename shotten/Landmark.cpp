#include "Landmark.h"

Landmark::Landmark()
{
	this->status = LandMarkStatus::UNFINISHED;
	this->player_1_cards = std::vector<Card>();
	this->player_2_cards = std::vector<Card>();
}

bool Landmark::isFinished()
{
	return this->player_1_cards.size() >= 3 && this->player_2_cards.size() >= 3;
}

bool Landmark::isColorRun(PlayerNumber number)
{
	if (this->isColor(number) && this->isRun(number)) 
		return true;
	return false;
}

bool Landmark::isThreeKind(PlayerNumber number)
{
	std::vector<Card> current_cards;
	if (number == PlayerNumber::ONE) {
		current_cards = this->player_1_cards;
	}
	else {
		current_cards = this->player_2_cards;
	}
	return current_cards[0].getNumber() == current_cards[1].getNumber() == current_cards[2].getNumber();
}

bool Landmark::isColor(PlayerNumber number)
{
	std::vector<Card> current_cards;
	if (number == PlayerNumber::ONE) {
		current_cards = this->player_1_cards;
	}
	else {
		current_cards = this->player_2_cards;
	}
	CardColor current_color = current_cards.front().getColor();
	for (Card card : current_cards) {
		if (card.getColor() != current_color) {
			return false;
		}
	}
	return true;
}

bool Landmark::isRun(PlayerNumber number)
{
	std::vector<Card> current_cards;
	if (number == PlayerNumber::ONE) {
		current_cards = this->player_1_cards;
	}
	else {
		current_cards = this->player_2_cards;
	}
	auto compare_temp = [](Card& a, Card& b)
	{
		return a.getNumber() < b.getNumber();
	};
	int min_val = (*std::min_element(current_cards.begin(), current_cards.end(), compare_temp)).getNumber();
	int max_val = (*std::max_element(current_cards.begin(), current_cards.end(), compare_temp)).getNumber();
	return (max_val - min_val == 2);
}

Combination Landmark::getCombination(PlayerNumber number)
{
	if (this->isColorRun(number)) {
		return Combination::COLOR_RUN;
	}
	else if (this->isThreeKind(number)) {
		return Combination::THREE_KIND;
	}
	else if (this->isColor(number)) {
		return Combination::COLOR;
	}
	else if (this->isRun(number)) {
		return Combination::RUN;
	}
	else {
		return Combination::SUM;
	}
}

std::vector<Card> Landmark::getCards(PlayerNumber number)
{
	switch (number) {
	case PlayerNumber::ONE:
		return this->player_1_cards;
	case PlayerNumber::TWO:
		return this->player_2_cards;
	default:
		std::cout << "WARNING: Unknown player number for landmark, getting cards from first landmark\n";
		return this->player_1_cards;
	}
}

int Landmark::getPoints(PlayerNumber number)
{
	int points = 0;
	std::vector<Card> current_cards;
	if (number == PlayerNumber::ONE) {
		current_cards = this->player_1_cards;
	}
	else {
		current_cards = this->player_2_cards;
	}
	for (auto card : current_cards) {
		points += card.getNumber();
	}
	return points;
}

bool Landmark::winPossibility(Player player, PlayerNumber waiting, PlayerNumber versus)
{
	int waitingCards = 0;
	int versusCards = 0;
	std::vector<Card>* versusDeck;
	if (waiting == PlayerNumber::ONE) {
		waitingCards = this->player_1_cards.size();
		versusCards = this->player_2_cards.size();
		versusDeck = &this->player_2_cards;
	}
	else {
		waitingCards = this->player_2_cards.size();
		versusCards = this->player_1_cards.size();
		versusDeck = &this->player_1_cards;
	}

	if(waitingCards == 3){
		Combination waitingCombination = this->getCombination(waiting);
		if(versusCards==2){
			for(auto card : player.getHand()){
				versusDeck->push_back(card);	
				Combination versusCombination = this->getCombination(versus);
				if(waitingCombination < versusCombination){
					versusDeck->pop_back();
					return false;
				}else if(waitingCombination == versusCombination){
					if(this->getPoints(waiting) < this->getPoints(versus)){
						versusDeck->pop_back();
						return false;
					}
				}
				versusDeck->pop_back();
			}
			return true;
		}else if(versusCards==1){
			for(auto card : player.getHand()){
				versusDeck->push_back(card);
				for(auto card2 : player.getHand()){
					if(card.getColor() != card2.getColor() && card.getNumber() != card2.getNumber()){
						versusDeck->push_back(card2);
						Combination versusCombination = this->getCombination(versus);
						if(waitingCombination < versusCombination){
							versusDeck->pop_back();
							versusDeck->pop_back();
							return false;
						}else if(waitingCombination == versusCombination){
							if(this->getPoints(waiting) < this->getPoints(versus)){
								versusDeck->pop_back();
								versusDeck->pop_back();
								return false;
							}
						}
						versusDeck->pop_back();
					}
				}
				versusDeck->pop_back();
			}
			return true;
		}else if(versusCards==0){
			for(auto card : player.getHand()){
				versusDeck->push_back(card);
				for(auto card2 : player.getHand()){
					if(card.getColor() != card2.getColor() && card.getNumber() != card2.getNumber()){
						versusDeck->push_back(card2);
						for(auto card3 : player.getHand()){
							if(card3.getColor() != card2.getColor() && card3.getNumber() != card2.getNumber() && card3.getColor() != card.getColor() && card3.getNumber() != card.getNumber()){
								versusDeck->push_back(card3);
								Combination versusCombination = this->getCombination(versus);
								if(waitingCombination < versusCombination){
									versusDeck->pop_back();
									versusDeck->pop_back();
									versusDeck->pop_back();
									return false;

									if(this->getPoints(waiting) < this->getPoints(versus)){
										versusDeck->pop_back();
										versusDeck->pop_back();
										versusDeck->pop_back();
										return false;
									}
								}
								versusDeck->pop_back();
							}
						}
						versusDeck->pop_back();
					}
				}
				versusDeck->pop_back();
			}
			return true;	
		}
	}
	return false;
}

void Landmark::addCard(Card card, PlayerNumber number)
{
	switch (number) {
	case PlayerNumber::ONE:
		this->player_1_cards.push_back(card);
		break;
	case PlayerNumber::TWO:
		this->player_2_cards.push_back(card);
		break;
	default:
		std::cout << "WARNING: Unknown player number for landmark, adding card to first landmark\n";
		this->player_1_cards.push_back(card);
	}
}

LandMarkStatus Landmark::getStatus()
{
	return LandMarkStatus();
}

void Landmark::setStatus(LandMarkStatus status)
{
	this->status = status;
}

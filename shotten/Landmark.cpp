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

bool Landmark::isColorRun(std::vector<Card> current_cards)
{
	if (this->isColor(current_cards) && this->isRun(current_cards)) 
		return true;
	return false;
}

bool Landmark::isThreeKind(std::vector<Card> current_cards)
{
	return current_cards[0].getNumber() == current_cards[1].getNumber() == current_cards[2].getNumber();
}

bool Landmark::isColor(std::vector<Card> current_cards)
{
	CardColor current_color = current_cards.front().getColor();
	for (Card card : current_cards) {
		if (card.getColor() != current_color) {
			return false;
		}
	}
	return true;
}

bool Landmark::isRun(std::vector<Card> current_cards)
{
	auto compare_temp = [](Card& a, Card& b)
	{
		return a.getNumber() < b.getNumber();
	};
	int min_val = (*std::min_element(current_cards.begin(), current_cards.end(), compare_temp)).getNumber();
	int max_val = (*std::max_element(current_cards.begin(), current_cards.end(), compare_temp)).getNumber();
	return (max_val - min_val == 2);
}

std::string Landmark::combinationType(Combination cbn)
{
	switch (cbn) {
	case Combination::SUM:
		return "SUM";
		break;
	case Combination::RUN:
		return "RUN";
		break;
	case Combination::COLOR:
		return "COLOR";
		break;
	case Combination::THREE_KIND:
		return "THREE_KIND";
		break;
	case Combination::COLOR_RUN:
		return "COLOR_RUN";
		break;
	default:
		return "UNKNOWN";
		break;
	}
}

Combination Landmark::getCombination(std::vector<Card> current_cards)
{
	if (this->isColorRun(current_cards)) {
		return Combination::COLOR_RUN;
	}
	else if (this->isThreeKind(current_cards)) {
		return Combination::THREE_KIND;
	}
	else if (this->isColor(current_cards)) {
		return Combination::COLOR;
	}
	else if (this->isRun(current_cards)) {
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

int Landmark::getPoints(std::vector<Card> current_cards)
{
	int points = 0;
	for (auto card : current_cards) {
		points += card.getNumber();
	}
	return points;
}

bool Landmark::winPossibility(Player player, PlayerNumber waiting, PlayerNumber versus, Deck deck)
{
	int nbWaitingCards = 0;
	int nbVersusCards = 0;
	std::vector<Card> versusDeck;
	std::vector<Card> cardList = deck.getDeck();
	std::vector<Card> waitingCards;
	if (waiting == PlayerNumber::ONE) {
		nbWaitingCards = this->player_1_cards.size();
		nbVersusCards = this->player_2_cards.size();
		versusDeck = this->player_2_cards;
		waitingCards = this->player_1_cards;
	}
	else {
		nbWaitingCards = this->player_2_cards.size();
		nbVersusCards = this->player_1_cards.size();
		versusDeck = this->player_1_cards;
		waitingCards = this->player_2_cards;
	}
	//add cardList and player.getHand() to cardList
	for (auto card : player.getHand()) {
		cardList.push_back(card);
	}
	
	
	if(nbWaitingCards == 3){
		Combination waitingCombination = this->getCombination(waitingCards);
		if(nbVersusCards==2){
			for(auto card : cardList){
				versusDeck.push_back(card);
				Combination versusCombination = this->getCombination(versusDeck);
				std::cout<<"waitingCombination : "<<combinationType(waitingCombination)<<std::endl;
				std::cout<<"versusCombination : "<<combinationType(versusCombination)<<std::endl;
				if(waitingCombination < versusCombination){
					return false;
				}else if(waitingCombination == versusCombination){
					std::cout<<"waiting : "<<this->getPoints(waitingCards)<<std::endl;
					std::cout<<"versus : "<<this->getPoints(versusDeck)<<std::endl;
					if(this->getPoints(waitingCards) < this->getPoints(versusDeck)){
						return false;
					}
				}
				versusDeck.pop_back();
			}
			return true;
		}else if(nbVersusCards==1){
			for(auto card : cardList){
				versusDeck.push_back(card);
				for(auto card2 : cardList){
					if(card.getColor() != card2.getColor() && card.getNumber() != card2.getNumber()){
						versusDeck.push_back(card2);
						Combination versusCombination = this->getCombination(versusDeck);
						if(waitingCombination < versusCombination){
							return false;
						}else if(waitingCombination == versusCombination){
							if(this->getPoints(waitingCards) < this->getPoints(versusDeck)){
								return false;
							}
						}
						versusDeck.pop_back();
					}
				}
				versusDeck.pop_back();
			}
			return true;
		}else if(nbVersusCards==0){
			for(auto card : cardList){
				versusDeck.push_back(card);
				for(auto card2 : cardList){
					if(card.getColor() != card2.getColor() && card.getNumber() != card2.getNumber()){
						versusDeck.push_back(card2);
						for(auto card3 : cardList){
							if(card3.getColor() != card2.getColor() && card3.getNumber() != card2.getNumber() && card3.getColor() != card.getColor() && card3.getNumber() != card.getNumber()){
								versusDeck.push_back(card3);
								Combination versusCombination = this->getCombination(versusDeck);
								if(waitingCombination < versusCombination){
									return false;

									if(this->getPoints(waitingCards) < this->getPoints(versusDeck)){
										return false;
									}
								}
								versusDeck.pop_back();
							}
						}
						versusDeck.pop_back();
					}
				}
				versusDeck.pop_back();
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


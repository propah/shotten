#pragma once
#include "Card.h"
#include "Player.h"
#include "Deck.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

enum class LandMarkStatus {
	UNFINISHED,
	FINISHED,
	WINNER_1,
	WINNER_2,
	WAITING_1,
	WAITING_2,
};

enum class Combination {
	SUM,
	RUN,
	COLOR,
	THREE_KIND,
	COLOR_RUN
};

class Landmark
{
private:
	std::vector<Card> player_2_cards;
	std::vector<Card> player_1_cards;
	bool isFinished();
	LandMarkStatus status;
	bool isColorRun(std::vector<Card> current_cards);
	bool isThreeKind(std::vector<Card> current_cards);
	bool isColor(std::vector<Card> current_cards);
	bool isRun(std::vector<Card> current_cards);
public:
	Landmark();
	std::vector<Card> getCards(PlayerNumber number);
	void addCard(Card card, PlayerNumber number);
	LandMarkStatus getStatus();
	Combination getCombination(std::vector<Card> current_cardr);
	int getPoints(std::vector<Card> current_cards);
	void setStatus(LandMarkStatus status);
	bool winPossibility(Player player, PlayerNumber waiting, PlayerNumber versus, Deck deck);
	std::string combinationType(Combination cbn);
};


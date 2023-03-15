#pragma once
#include "Card.h"
#include "Player.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

enum class LandMarkStatus {
	UNFINISHED,
	FINISHED,
	WAITING_1,
	WAITING_2
};

enum class Combination {
	COLOR_RUN,
	THREE_KIND,
	COLOR,
	RUN,
	SUM
};

class Landmark
{
private:
	std::vector<Card> player_2_cards;
	std::vector<Card> player_1_cards;
	bool isFinished();

	bool isColorRun(PlayerNumber number);
	bool isThreeKind(PlayerNumber number);
	bool isColor(PlayerNumber number);
	bool isRun(PlayerNumber number);
public:
	Landmark();
	std::vector<Card> getCards(PlayerNumber number);
	void addCard(Card card, PlayerNumber number);
	LandMarkStatus getStatus();
	Combination getCombination(PlayerNumber number);
};


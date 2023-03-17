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

	bool isColorRun(PlayerNumber number) const;
	bool isThreeKind(PlayerNumber number) const;
	bool isColor(PlayerNumber number) const;
	bool isRun(PlayerNumber number) const;
public:
	Landmark();
	std::vector<Card> getCards(PlayerNumber number) const;
	void addCard(Card card, PlayerNumber number);
	LandMarkStatus getStatus() const;
	Combination getCombination(PlayerNumber number) const;
};


#pragma once
#include "Board.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>
class Game
{
private:
	Deck deck;
	Board board;
	Player player1;
	Player player2;
	int current_player;
public:
	Game();
	void nextTurn();
	int checkWinner();
	void updateStatus(int position);
};


#include "Game.h"

Game::Game()
{
	this->board = Board();
	this->deck = Deck();
	this->player1 = Player();
	this->player2 = Player();
	this->current_player = 1;
	for (int i = 0; i < 6; i++) {
		Option<Card> temp = this->deck.drawCard();
		if (temp) {
			this->player1.addCard(temp.value());
		}
		temp = this->deck.drawCard();
		if (temp) {
			this->player2.addCard(temp.value());
		}
	}
}

void Game::nextTurn()
{
	if (system("CLS")) system("clear");
	int input_card_num = 0;
	int input_landmark_num = 0;
	Card selected_card = Card(0, CardColor::BLUE);
	Landmark selected_landmark = Landmark();
	this->board.display();
	if (this->current_player == 1) {
		player1.displayHand();
		std::cout << "Enter the card number you want to play (1 to 6):";
		std::cin >> input_card_num;
		selected_card = this->player1.getHand()[input_card_num - 1];
		std::cout << "Enter the landmark you want to play (1 to 9):";
		std::cin >> input_landmark_num;
		selected_landmark = board.getLandMark(input_landmark_num - 1);

		this->player1.removeCard(selected_card);
		this->board.placeCard(input_landmark_num - 1, selected_card, PlayerNumber::ONE);
		auto temp = this->deck.drawCard();
		if (temp) {
			this->player1.addCard(temp.value());
		}
		this->current_player = 2;
	}
	else {
		player2.displayHand();
		std::cout << "Enter the card number you want to play (1 to 6):";
		std::cin >> input_card_num;
		selected_card = this->player2.getHand()[input_card_num - 1];
		std::cout << "Enter the landmark you want to play (1 to 9):";
		std::cin >> input_landmark_num;
		this->player2.removeCard(selected_card);
		this->board.placeCard(input_landmark_num - 1, selected_card, PlayerNumber::TWO);
		auto temp = this->deck.drawCard();
		if (temp) {
			this->player2.addCard(temp.value());
		}
		this->current_player = 1;
	}
}

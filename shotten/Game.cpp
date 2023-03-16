#include "Game.h"
#include "Landmark.h"

Game::Game()
{
	this->board = Board();
	this->deck = Deck();
	this->player1 = Player();
	this->player2 = Player();
	this->current_player = 1;
	for (int i = 0; i < 6; i++) {
		auto temp = this->deck.drawCard();
		if (temp.has_value()) {
			this->player1.addCard(temp.value());
		}
		temp = this->deck.drawCard();
		if (temp.has_value()) {
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
		if (temp.has_value()) {
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
		if (temp.has_value()) {
			this->player2.addCard(temp.value());
		}
		this->current_player = 1;
	}
}

void Game::updateStatus(int position)
{
	Landmark landmark = this->board.getLandMark(position);
	std::vector<Card> player1Card = landmark.getCards(PlayerNumber::ONE);
	std::vector<Card> player2Card = landmark.getCards(PlayerNumber::TWO);
	if (player1Card.size() == 3 && player2Card.size() < 3) {
		landmark.setStatus(LandMarkStatus::WAITING_2);
	}else if (player2Card.size() == 3 && player1Card.size() < 3) {
		landmark.setStatus(LandMarkStatus::WAITING_1);
	}else if (player1Card.size() == 3 && player2Card.size() == 3) {
		landmark.setStatus(LandMarkStatus::FINISHED);
		this->checkWinner();
	}
}

void Game::checkWaiting(int position){
	Landmark landmark = this->board.getLandMark(position);
	std::vector<Card> player1Card = landmark.getCards(PlayerNumber::ONE);
	std::vector<Card> player2Card = landmark.getCards(PlayerNumber::TWO);
	if(landmark.getStatus() == LandMarkStatus::WAITING_1 && player1Card.size() == 3){
		
	}
}

int Game::checkWinner()
{
	std::vector<Landmark> landmark = this->board.getLandmarks();
	int player1Streak = 0;
	int player2Streak = 0;
	int player1Total = 0;
	int player2Total = 0;
	for (int i = 0; i < 9; i++) {
		LandMarkStatus gameStatus = landmark[i].getStatus();
		if (gameStatus == LandMarkStatus::FINISHED) {
			Combination combination1 = landmark[i].getCombination(PlayerNumber::ONE);
			Combination combination2 = landmark[i].getCombination(PlayerNumber::TWO);
			if(combination1 == combination2) {
				int player1Pts = landmark[i].getPoints(PlayerNumber::ONE);
				int player2Pts = landmark[i].getPoints(PlayerNumber::TWO);
				landmark[i].setStatus(player1Pts > player2Pts ? LandMarkStatus::WINNER_1 : LandMarkStatus::WINNER_2);	
			}else{
				landmark[i].setStatus(combination1 > combination2 ? LandMarkStatus::WINNER_1 : LandMarkStatus::WINNER_2);
			}
		}
		if(gameStatus == LandMarkStatus::WAITING_1 || gameStatus == LandMarkStatus::WAITING_2){
			
			return 0;
		}
		if (landmark[i].getStatus() == LandMarkStatus::WINNER_1) {
			player1Streak++;
			player1Total += landmark[i].getPoints(PlayerNumber::ONE);
			player2Streak = 0;	
		}
		else if (landmark[i].getStatus() == LandMarkStatus::WINNER_2) {
			player2Streak++;
			player2Total += landmark[i].getPoints(PlayerNumber::TWO);
			player1Streak = 0;
		}else{
			player1Streak = 0;
			player2Streak = 0;
		}
		if(player1Streak == 3 || player2Streak == 3){
			return player1Streak == 3 ? 1 : 2;
		}else if(player1Total == 5 || player2Total == 5){
			return player1Total == 5 ? 1 : 2;
		}
		//TODO: check if 3 in a row or 5
	}
	return 0;
}

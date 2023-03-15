#include "Game.h"
#include "SFML/Graphics.hpp"

int main() {
	Game game = Game();
	while (true) {
		game.nextTurn();
	}
}
   
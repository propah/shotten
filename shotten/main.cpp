#include "SFML/Graphics.hpp"
#include "Game.h"

int main() {
	Game game = Game();
	while (true) {
		game.nextTurn();
	}
}
   
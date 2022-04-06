

#include "Game.h"
#include "GamePlay.h"
#include "Constants.h"

int GamePlay::level = 1;

int main() {
	srand((unsigned int)time(NULL));
	Game game;
	game.Run();
	return 0;
}

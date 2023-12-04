#include <Game.h>

const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 900;

int main()
{
	Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
	game.start();
}


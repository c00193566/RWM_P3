#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Game.h"

using namespace std;

int main(int argc, char* argv[])
{
	Game* game = new Game();
	cout << "Game Object Created" << endl;

	game->Initialize();
	cout << "Game Initialized" << endl;

	cout << "Game Loop Starting..." << endl;

	while (game->IsRunning())
	{
		game->Update();
	}

	game->CleanUp();
	cout << "Clean Up" << endl;

	SDL_Quit();

	return 0;
}
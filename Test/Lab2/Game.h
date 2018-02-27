#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <MenuComponentSystem.h>
#include <TextureHandler.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

enum class GameStates
{
	MainMenu,
	Play,
	Options
};

class Game {
private:
	GameStates CurrentState;

	bool isRunning;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	
	// Texture Handler
	TextureHandler * TextureManagement;

	// Menu Elements
	MenuSystem MainMenu;
	MenuSystem OptionMenu;
	int MouseX;
	int MouseY;

	Sprite TestSprite;

	//Frame Rate Testing
	Uint32 TickStart;
	float FramesPerSecond;

public:
	void Initialize();
	void HandleEvents();
	void Update();
	void Render();
	void CleanUp() {};

	GameStates String_To_GameState(string);

	bool IsRunning() { return isRunning; };
};
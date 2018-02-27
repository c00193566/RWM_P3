#include "Game.h"

void Game::Initialize() 
{
	isRunning = true;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Testing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	CurrentState = GameStates::MainMenu;

	TextureManagement = TextureHandler::Instance();
	TextureManagement->addTexture("Play", "Assets/Play.png", renderer);

	MainMenu.SetUsingImages(false);

	OptionMenu.SetUsingImages(true);

	MainMenu.SetUpdateType("KEYBOARD", SDL_Color{ 0, 255, 0, 255 });
	OptionMenu.SetUpdateType("MOUSE", SDL_Color{ 0, 255, 0, 255 });

	SDL_Rect position;
	position.x = 640;
	position.y = 180;
	position.w = 64;
	position.h = 64;

	SDL_Rect sheet;
	sheet.x = 0;
	sheet.y = 0;
	sheet.w = 321;
	sheet.h = 321;

	//OptionMenu.AddImage("Assets/Play.png", "Play", position, true, sheet, 1, "Horizontal", renderer, true);
	OptionMenu.AddImage(TextureManagement->getTexture("Play"), "Play", position, true, sheet, 1, "Horizontal", renderer, true);

	MainMenu.AddText("Assets/OpenSans.ttf", "Play", position, true, renderer, true, SDL_Color{ 255, 255, 0, 255 }, SDL_Color{ 255, 0, 255, 255 });

	position.y = 360;

	MainMenu.AddText("Assets/OpenSans.ttf", "Options", position, true, renderer, true, SDL_Color{ 255, 255, 0, 255 }, SDL_Color{ 255, 0, 255, 255 });
	
	OptionMenu.AddImage("Assets/Options.png", "Menu", position, true, sheet, 1, "Horizontal", renderer, true);

	TestSprite = Sprite("Assets/SpecOps.png", renderer, SDL_Rect{ 0, 0, 136, 136 }, SDL_Rect{ 200, 200, 64, 64 });
	TestSprite.setOrigin();
	TestSprite.setRotation(180);

	//Frame Rate Testing
	FramesPerSecond = 10000.0f / 80.0f;

}

void Game::HandleEvents()
{
	SDL_Event localEvent;

	while (SDL_PollEvent(&localEvent))
	{
		if (localEvent.type == SDL_QUIT)
		{
			isRunning = false;
		}

		if (CurrentState == GameStates::MainMenu)
		{
			MainMenu.SystemUpdate(&localEvent, renderer);
		}
		else if (CurrentState == GameStates::Options)
		{
			OptionMenu.SystemUpdate(&localEvent, renderer);
		}
		
		if (localEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			if (localEvent.button.button == SDL_BUTTON_LEFT)
			{
				string temp;
				if (CurrentState == GameStates::MainMenu)
				{
					temp = MainMenu.onClick();
				}
				else if (CurrentState == GameStates::Options)
				{
					temp = OptionMenu.onClick();
				}
				cout << temp << endl;
				if (temp != "NONE")
				{
					CurrentState = String_To_GameState(temp);
				}
			}
		}

		if (localEvent.type == SDL_KEYDOWN)
		{
			if (localEvent.key.keysym.sym == SDLK_RETURN)
			{
				string temp;
				if (CurrentState == GameStates::MainMenu)
				{
					temp = MainMenu.onClick();
				}
				else if (CurrentState == GameStates::Options)
				{
					temp = OptionMenu.onClick();
				}
				cout << temp << endl;
				if (temp != "NONE")
				{
					CurrentState = String_To_GameState(temp);
				}
			}
		}
	}
}

void Game::Update()
{
	TickStart = SDL_GetTicks();

	// Events
	HandleEvents();

	// Update functions called here
	//MainMenu.MouseImageUpdate(MouseX, MouseY);
	//

	TestSprite.addRotation(1);

	// Render
	Render();

	if (FramesPerSecond > SDL_GetTicks() - TickStart)
	{
		SDL_Delay(FramesPerSecond - (SDL_GetTicks() - TickStart));
	}

}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	if (CurrentState == GameStates::MainMenu)
	{
		MainMenu.Render(renderer);
	}
	else if (CurrentState == GameStates::Options)
	{
		OptionMenu.Render(renderer);
	}

	TestSprite.Render(renderer);

	SDL_RenderPresent(renderer);
}

GameStates Game::String_To_GameState(string State)
{
	if (State == "Play")
	{
		return GameStates::Play;
	}
	else if (State == "Options")
	{
		return GameStates::Options;
	}
	else if (State == "Menu")
	{
		return GameStates::MainMenu;
	}
}

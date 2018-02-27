#include "Text.h"

Text::Text(string filepath, SDL_Renderer * renderer, string Tag, SDL_Rect Position, SDL_Color NonHighlighted, SDL_Color Highlighted)
{
	// Load Font
	if (TTF_Init() == -1)
	{
		printf("TTF_Init: %s\n", TTF_GetError());
	}

	Font = TTF_OpenFont(filepath.c_str(), 24);

	if (!Font)
	{
		cout << "Failed to load font" << endl;
	}

	// Set up Colours
	TextOriginalColour = NonHighlighted;
	TextAlternativeColour = Highlighted;

	// Set Position
	TextPosition = Position;

	TextWord = Tag;

	TextSurface = TTF_RenderText_Solid(Font, TextWord.c_str(), TextOriginalColour);
	TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);

	// Set correct width and height
	int w, h;
	SDL_QueryTexture(TextTexture, NULL, NULL, &w, &h);

	TextPosition.w = w;
	TextPosition.h = h;
}

void Text::setOrigin()
{
	int w, h;
	SDL_QueryTexture(TextTexture, NULL, NULL, &w, &h);

	TextPosition.w = w;
	TextPosition.h = h;

	TextPosition.x -= TextPosition.w / 2;
	TextPosition.y -= TextPosition.h / 2;
}

void Text::Render(SDL_Renderer * Renderer)
{
	SDL_RenderCopy(Renderer, TextTexture, NULL, &TextPosition);
}

void Text::setPosition(float x, float y)
{
	TextPosition.x = x;
	TextPosition.y = y;
}

void Text::setPosition(SDL_Rect rect)
{
	TextPosition.x = rect.x;
	TextPosition.y = rect.y;
}

void Text::SwitchTextColour(SDL_Renderer * renderer, bool Intersected)
{
	if (Intersected)
	{
		TextSurface = TTF_RenderText_Solid(Font, TextWord.c_str(), TextAlternativeColour);
		TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);
	}
	else
	{
		TextSurface = TTF_RenderText_Solid(Font, TextWord.c_str(), TextOriginalColour);
		TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);
	}
}

void Text::setSize(float w, float h)
{
	TextPosition.w = w;
	TextPosition.h = h;
}

void Text::setSize(SDL_Rect rect)
{
	TextPosition.w = rect.w;
	TextPosition.h = rect.h;
}


#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>

using namespace std;

class Text
{
public:
	Text() {};
	~Text() {};
	Text(string filepath, SDL_Renderer * renderer, string Tag, SDL_Rect Position, SDL_Color NonHighlighted, SDL_Color Highlighted);

	// Set Origin
	void setOrigin();

	// Renderers
	void Render(SDL_Renderer* r);

	// Set Position
	void setPosition(float x, float y);
	void setPosition(SDL_Rect rect);

	// Change Text Colour
	void SwitchTextColour(SDL_Renderer * renderer, bool Intersected);

	// Set Size
	void setSize(float w, float h);
	void setSize(SDL_Rect rect);

	// Get Sheet Coordinates
	SDL_Rect getPosition() { return TextPosition; };

private:
	TTF_Font * Font;
	SDL_Color TextOriginalColour;
	SDL_Color TextAlternativeColour;
	SDL_Surface* TextSurface;
	SDL_Texture* TextTexture;
	SDL_Rect TextPosition;
	string TextWord;
};
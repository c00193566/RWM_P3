#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

using namespace std;

class Sprite
{
public:
	Sprite() {};
	~Sprite() {};
	Sprite(string filepath, SDL_Renderer * renderer, SDL_Rect Source, SDL_Rect Screen);
	Sprite(SDL_Texture * Texture, SDL_Rect Source, SDL_Rect Screen);

	// Set Origin
	void setOrigin();
	void setOrigin(float x, float y);

	// Renderers
	void Render(SDL_Renderer* r, int angle);
	void Render(SDL_Renderer* r);

	// Set Position
	void setPosition(float x, float y);
	void setPosition(SDL_Rect rect);

	// Set Sheet Position
	void setSheetPosition(float x, float y);
	void setSheetPosition(SDL_Rect rect);

	// Set Size
	void setSize(float x, float y);
	void setSize(SDL_Rect rect);

	// Set Rotation
	void setRotation(float angle);
	void addRotation(float value);

	// Get Sheet Coordinates
	SDL_Rect getSpriteDimensions() { return SheetRect; };

	// Get Screen Coordinates
	SDL_Rect getScreenCoords() { return ScreenRect; };

private:
	SDL_Texture * Texture;
	SDL_Rect SheetRect;
	SDL_Rect ScreenRect;
	SDL_Point Origin;
	SDL_RendererFlip Flip;
	float Rotation;
};
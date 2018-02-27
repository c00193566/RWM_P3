#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <map>

using namespace std;

class TrianglePrimitive
{
private:
	map<int, SDL_Point> Positions;
	map<int, string> TypeAtIndex;
	int CurrentPoisition;
	SDL_Point PointTwoDiffernce;
	SDL_Point PointThreeDiffernce;
	int MAPINDEX;
	SDL_Color DrawColour;

public:
	TrianglePrimitive(SDL_Color Colour = SDL_Color{ 255, 255, 255, 255 });
	void AddPosition(SDL_Point, string);
	void Render(SDL_Renderer * Renderer);
	void MoveDown();
	void MoveUp();

	string CurrentType() { return TypeAtIndex[CurrentPoisition]; };
};
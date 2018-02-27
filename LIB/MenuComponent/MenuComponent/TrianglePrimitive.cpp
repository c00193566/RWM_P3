#include "TrianglePrimitive.h"

TrianglePrimitive::TrianglePrimitive(SDL_Color Colour)
{
	MAPINDEX = 0;

	CurrentPoisition = 0;

	PointTwoDiffernce.x = -32;
	PointTwoDiffernce.y = -16;

	PointThreeDiffernce.x = -32;
	PointThreeDiffernce.y = 16;

	DrawColour = Colour;
}

void TrianglePrimitive::AddPosition(SDL_Point Point, string Type)
{
	Positions[MAPINDEX] = Point;
	TypeAtIndex[MAPINDEX] = Type;
	MAPINDEX++;
}

void TrianglePrimitive::Render(SDL_Renderer * Renderer)
{
	SDL_SetRenderDrawColor(Renderer, DrawColour.r, DrawColour.g, DrawColour.b, DrawColour.a);

	SDL_RenderDrawLine(Renderer, Positions[CurrentPoisition].x, Positions[CurrentPoisition].y,
		Positions[CurrentPoisition].x + PointTwoDiffernce.x, Positions[CurrentPoisition].y + PointTwoDiffernce.y);
	SDL_RenderDrawLine(Renderer, Positions[CurrentPoisition].x, Positions[CurrentPoisition].y,
		Positions[CurrentPoisition].x + PointThreeDiffernce.x, Positions[CurrentPoisition].y + PointThreeDiffernce.y);
	SDL_RenderDrawLine(Renderer, Positions[CurrentPoisition].x + PointTwoDiffernce.x, Positions[CurrentPoisition].y + PointTwoDiffernce.y,
		Positions[CurrentPoisition].x + PointThreeDiffernce.x, Positions[CurrentPoisition].y + PointThreeDiffernce.y);
}

void TrianglePrimitive::MoveDown()
{
	if (CurrentPoisition < MAPINDEX - 1)
	{
		CurrentPoisition++;
	}
}

void TrianglePrimitive::MoveUp()
{
	if (CurrentPoisition > 0)
	{
		CurrentPoisition--;
	}
}

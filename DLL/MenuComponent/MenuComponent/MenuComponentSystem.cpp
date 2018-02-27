#include "MenuComponentSystem.h"

void MenuSystem::SetUsingImages(bool set)
{
	Images = set;
}

bool MenuSystem::SetUpdateType(string Type, SDL_Colour Colour)
{
	UpdateType = Type;

	if (UpdateType == "KEYBOARD")
	{
		Indicator = new TrianglePrimitive(Colour);
	}

	if (UpdateType == "MOUSE" || UpdateType == "KEYBOARD")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MenuSystem::AddText(string Path, string Tag, SDL_Rect Position, bool Interact, SDL_Renderer * Renderer, bool CenterOrigin, SDL_Color TextColour, SDL_Color AlternateColour)
{
	if (!Images)
	{
		TextObjects[Tag] = new Text(Path, Renderer, Tag, Position, TextColour, AlternateColour);
		InteractableObjects[Tag] = Interact;
		ObjectFrames[Tag] = 1;
		CurrentFrame[Tag] = 0;

		if (CenterOrigin)
		{
			TextObjects[Tag]->setOrigin();
		}

		if (UpdateType == "KEYBOARD" && Indicator != nullptr)
		{
			SDL_Point Point;

			Point = SDL_Point{ TextObjects[Tag]->getPosition().x - 128, TextObjects[Tag]->getPosition().y + TextObjects[Tag]->getPosition().h / 2 };

			Indicator->AddPosition(Point, Tag);
		}

		return true;
	}
	else
	{
		cout << "Could not add Text." << endl;
		cout << "Please SetUsingImages to false." << endl;
		return false;
	}
}

bool MenuSystem::AddImage(string Path, string Tag, SDL_Rect Position, bool Interact, SDL_Rect SpriteSheet, int Frames, string Direction,
	SDL_Renderer * Renderer, bool CenterOrigin, int Layer)
{
	if (Images)
	{
		SpriteObjects[Tag] = new Sprite(Path, Renderer, SpriteSheet, Position);
		InteractableObjects[Tag] = Interact;
		ObjectFrames[Tag] = Frames;
		CurrentFrame[Tag] = 0;
		ObjectLayer[Tag] = Layer;

		if (CenterOrigin)
		{
			SpriteObjects[Tag]->setOrigin();
		}

		if (Direction != "Horizontal" && Direction != "Vertical" && Direction != "None")
		{
			return false;
		}
		else
		{
			DirectionCycle[Tag] = Direction;
		}

		if (UpdateType == "KEYBOARD" && Indicator != nullptr)
		{
			SDL_Point Point;

			Point = SDL_Point{ SpriteObjects[Tag]->getScreenCoords().x - 128, SpriteObjects[Tag]->getScreenCoords().y + SpriteObjects[Tag]->getScreenCoords().h / 2 };

			Indicator->AddPosition(Point, Tag);
		}

		return true;
	}
	else
	{
		cout << "Could not add Image." << endl;
		cout << "Please SetUsingImages to true." << endl;
		return false;
	}
}

bool MenuSystem::AddImage(SDL_Texture * IMG, string Tag, SDL_Rect Position, bool Interact, SDL_Rect SpriteSheet, int Frames, string Direction,
	SDL_Renderer * Renderer, bool CenterOrigin, int Layer)
{
	if (Images)
	{
		SpriteObjects[Tag] = new Sprite(IMG, SpriteSheet, Position);
		InteractableObjects[Tag] = Interact;
		ObjectFrames[Tag] = Frames;
		CurrentFrame[Tag] = 0;
		ObjectLayer[Tag] = Layer;

		if (CenterOrigin)
		{
			SpriteObjects[Tag]->setOrigin();
		}

		if (Direction != "Horizontal" && Direction != "Vertical" && Direction != "None")
		{
			return false;
		}
		else
		{
			DirectionCycle[Tag] = Direction;
		}

		if (UpdateType == "KEYBOARD" && Indicator != nullptr)
		{
			SDL_Point Point;

			Point = SDL_Point{ SpriteObjects[Tag]->getScreenCoords().x - 128, SpriteObjects[Tag]->getScreenCoords().y + SpriteObjects[Tag]->getScreenCoords().h / 2 };

			Indicator->AddPosition(Point, Tag);
		}

		return true;
	}
	else
	{
		cout << "Could not add Image." << endl;
		cout << "Please SetUsingImages to true." << endl;
		return false;
	}
}

void MenuSystem::Render(SDL_Renderer * Renderer)
{
	if (Images)
	{
		map<string, Sprite*>::iterator iter;

		for (iter = SpriteObjects.begin(); iter != SpriteObjects.end(); iter++)
		{
			if (ObjectLayer[iter->first] == 0)
			{
				iter->second->Render(Renderer);
			}
		}

		for (iter = SpriteObjects.begin(); iter != SpriteObjects.end(); iter++)
		{
			if (ObjectLayer[iter->first] == 1)
			{
				iter->second->Render(Renderer);
			}
		}
	}
	else
	{
		map<string, Text*>::iterator iter;

		for (iter = TextObjects.begin(); iter != TextObjects.end(); iter++)
		{
			iter->second->Render(Renderer);
		}
	}

	if (UpdateType == "KEYBOARD")
	{
		Indicator->Render(Renderer);
	}
}

void MenuSystem::SystemUpdate(SDL_Event * Event, SDL_Renderer * Renderer)
{
	if (UpdateType == "MOUSE")
	{
		int MouseX;
		int MouseY;

		if (Event->type == SDL_MOUSEMOTION)
		{
			if (Images)
			{
				SDL_GetMouseState(&MouseX, &MouseY);
				MouseImageUpdate(MouseX, MouseY);
			}
			else
			{
				SDL_GetMouseState(&MouseX, &MouseY);
				MouseTextUpdate(MouseX, MouseY, Renderer);
			}
		}
	}
	else if (UpdateType == "KEYBOARD")
	{
		if (Event->type == SDL_KEYDOWN)
		{
			if (Event->key.keysym.sym == SDLK_DOWN)
			{
				Indicator->MoveDown();
			}
			else if (Event->key.keysym.sym == SDLK_UP)
			{
				Indicator->MoveUp();
			}

			Highlighted = Indicator->CurrentType();

			KeyboardTextUpdate(Renderer);
		}
	}
}

void MenuSystem::SystemUpdate(int X, int Y, SDL_Renderer * Renderer)
{
	if (UpdateType == "MOUSE")
	{
		int MouseX = X;
		int MouseY = Y;

		if (Images)
		{
			SDL_GetMouseState(&MouseX, &MouseY);
			MouseImageUpdate(MouseX, MouseY);
		}
		else
		{
			SDL_GetMouseState(&MouseX, &MouseY);
			MouseTextUpdate(MouseX, MouseY, Renderer);
		}
	}
}

void MenuSystem::MouseImageUpdate(int X, int Y)
{
	SDL_Rect Mouse;
	Mouse.x = X;
	Mouse.y = Y;
	Mouse.w = 1;
	Mouse.h = 1;

	map<string, Sprite*>::iterator iter;

	bool ImageHighlighted = false;

	for (iter = SpriteObjects.begin(); iter != SpriteObjects.end(); iter++)
	{
		string ObjectTag = iter->first;

		if (InteractableObjects[ObjectTag])
		{
			SDL_Rect Position = iter->second->getScreenCoords();

			if ((Mouse.x > Position.x && Mouse.x < Position.x + Position.w) &&
				(Mouse.y > Position.y && Mouse.y < Position.y + Position.h))
			{
				if (ObjectFrames[ObjectTag] > 0)
				{
					if (!(CurrentFrame[ObjectTag] >= ObjectFrames[ObjectTag]))
					{
						CurrentFrame[ObjectTag]++;

						SDL_Rect NewPosition = iter->second->getSpriteDimensions();

						if (DirectionCycle[ObjectTag] == "Horizontal")
						{
							NewPosition.x += NewPosition.w;
						}
						else if (DirectionCycle[ObjectTag] == "Vertical")
						{
							NewPosition.y += NewPosition.h;
						}


						iter->second->setSheetPosition(NewPosition);
					}
				}

				Highlighted = ObjectTag;

				ImageHighlighted = true;

			}
			else
			{
				if (ObjectFrames[ObjectTag] > 0)
				{

					if (CurrentFrame[ObjectTag] >= ObjectFrames[ObjectTag])
					{
						CurrentFrame[ObjectTag] = 0;

						SDL_Rect NewPosition = iter->second->getSpriteDimensions();

						NewPosition.x = 0;
						NewPosition.y = 0;

						iter->second->setSheetPosition(NewPosition);

					}
				}

				if (!ImageHighlighted)
				{
					Highlighted = "NONE";
				}
			}
		}
	}
}

void MenuSystem::MouseTextUpdate(int X, int Y, SDL_Renderer * Renderer)
{

	SDL_Rect Mouse;
	Mouse.x = X;
	Mouse.y = Y;
	Mouse.w = 1;
	Mouse.h = 1;

	map<string, Text*>::iterator iter;

	bool TextHighlighted = false;

	for (iter = TextObjects.begin(); iter != TextObjects.end(); iter++)
	{
		string ObjectTag = iter->first;
		if (InteractableObjects[ObjectTag])
		{
			SDL_Rect Position = iter->second->getPosition();

			if ((Mouse.x > Position.x && Mouse.x < Position.x + Position.w) &&
				(Mouse.y > Position.y && Mouse.y < Position.y + Position.h))
			{
				Highlighted = ObjectTag;
				iter->second->SwitchTextColour(Renderer, true);
				TextHighlighted = true;
			}
			else
			{
				iter->second->SwitchTextColour(Renderer, false);
				if (!TextHighlighted)
				{
					Highlighted = "NONE";
				}
			}
		}
	}
}

void MenuSystem::KeyboardTextUpdate(SDL_Renderer * Renderer)
{
	map<string, Text*>::iterator iter;

	for (iter = TextObjects.begin(); iter != TextObjects.end(); iter++)
	{
		if (iter->first == Highlighted)
		{ 
			iter->second->SwitchTextColour(Renderer, true);
		}
		else
		{
			iter->second->SwitchTextColour(Renderer, false);
		}
	}
}

#pragma once
#include <Windows.h>
#include <vector>
#include <map>
#include "Sprite.h"
#include "Text.h"
#include "TrianglePrimitive.h"
#include "SDL.h"
#include "SDL_image.h"

using namespace std;

class MenuSystem
{
private:
	bool Images;
	string UpdateType;
	string Highlighted;
	TrianglePrimitive * Indicator;
	map<string, Text*> TextObjects;
	map<string, Sprite*> SpriteObjects;
	map<string, bool> InteractableObjects;
	map<string, string> DirectionCycle;
	map<string, int> ObjectFrames;
	map<string, int> CurrentFrame;
	map<string, int> ObjectLayer;

public:
	/// <summary>
	/// Sets if the system will be using images or text.
	/// </summary>
	/// <param name="set">Use true to use images or false to use text.</param>
	void SetUsingImages(bool set);

	/// <summary>
	/// Decide if you want the system to update through keyboard input or mouse input.
	/// </summary>
	/// <param name="Type">string to set to keyboard or mouse. *KEYBOARD or MOUSE is accepted*</param>
	/// <param name="Colour">SDL_Colour to set the colour of the triangle for keyboard input. *Defaults to white*</param>
	bool SetUpdateType(string Type, SDL_Colour Colour = SDL_Color{ 255, 255, 255, 255 });

	/// <summary>
	/// 
	/// </summary>
	/// <param name="Path">The file location of the font to be used.</param>
	/// <param name="Tag">The tag which will identify the text and be used as the text.</param>
	/// <param name="Position">SDL_Rect to position the text and determine width and height.</param>
	/// <param name="Interact">a bool variable to determine if a user can interact with it.</param>
	/// <param name="Renderer">SDL_Renderer to allow the text to be drawn.</param>
	/// <param name="CenterOrigin">bool to check if user wants to set the origin of the text to the center</param>
	/// <param name="TextColour">SDL_Color to set the color of the text.</param>
	/// <param name ="AlternateColour">SDL_Color to set the color of the text when highlighted.</param>
	bool AddText(string Path, string Tag, SDL_Rect Position, bool Interact, SDL_Renderer * Renderer, bool CenterOrigin, SDL_Color TextColour, SDL_Color AlternateColour);

	/// <summary>
	/// Adds an image to the Menu System.
	/// </summary>
	/// <param name="Path">The file location of the image.</param>
	/// <param name="Tag">The tag which will identify the image</param>
	/// <param name="Position">SDL_Rect to position the image and determine width and height.</param>
	/// <param name="Interact">a bool variable to determine if a user can interact with it.</param>
	/// <param name="SpriteSheet">SDL_Rect to identify the position on the image file itself with a set width and height</param>
	/// <param name="Frames">int to determine if there is more than 1 frame. *0 frame = 0 Frames. No more than 1 frames.*</param>
	/// <param name="Direction">a string variable to determine how to cycle through the spritesheet. *Horizontal / Vertical / None*</param>
	/// <param name="Renderer">SDL_Renderer to allow the sprite to be drawn.</param>
	/// <param name="CenterOrigin">bool to check if user wants to set the origin of the image to the center</param>
	/// <param name="Layer">int this will ensure a set draw order. Use 0 for background and 1 for foreground.</param>
	bool AddImage(string Path, string Tag, SDL_Rect Position, bool Interact, SDL_Rect SpriteSheet, int Frames, string Direction,
		SDL_Renderer * Renderer, bool CenterOrigin, int Layer);

	/// <summary>
	/// Adds an image to the Menu System.
	/// </summary>
	/// <param name="IMG">SDL_Texture to assign to the sprite.</param>
	/// <param name="Tag">The tag which will identify the image</param>
	/// <param name="Position">SDL_Rect to position the image and determine width and height.</param>
	/// <param name="Interact">a bool variable to determine if a user can interact with it.</param>
	/// <param name="SpriteSheet">SDL_Rect to identify the position on the image file itself with a set width and height</param>
	/// <param name="Frames">int to determine if there is more than 1 frame. *0 frame = 0 Frames. No more than 1 frames.*</param>
	/// <param name="Direction">a string variable to determine how to cycle through the spritesheet. *Horizontal / Vertical / None*</param>
	/// <param name="Renderer">SDL_Renderer to allow the sprite to be drawn.</param>
	/// <param name="CenterOrigin">bool to check if user wants to set the origin of the image to the center</param>
	bool AddImage(SDL_Texture * IMG, string Tag, SDL_Rect Position, bool Interact, SDL_Rect SpriteSheet, int Frames, string Direction,
		SDL_Renderer * Renderer, bool CenterOrigin, int Layer);

	/// <summary>
	/// Renders Menu elements
	/// </summary>
	/// <param name="Renderer">SDL_Renderer to draw elements</param>
	void Render(SDL_Renderer * Renderer);

	/// <summary>
	/// Using the Update Type string the system will update using the relevant methods
	/// </summary>
	/// <param name="Event">SDL_Event will need to be passed in so events can be tracked.</param>
	void SystemUpdate(SDL_Event * Event, SDL_Renderer * Renderer);
	void SystemUpdate(int X, int Y, SDL_Renderer * Renderer);

	/// <summary>
	/// This method is set to return the current highlighted item.
	/// </summary>
	/// <returns>string the current highlighted item.</returns>
	string onClick() { return Highlighted; };

	/// <summary>
	/// Will check if the mouse has intersected an image and will
	/// update that image accordingly.
	/// </summary>
	/// <param name="X">The mouse's x position.</param>
	/// <param name="Y">The mouse's y position.</param>
	void MouseImageUpdate(int X, int Y);

	/// <summary>
	/// Will check if the mouse has intersected a text area and will
	/// update that image accordingly.
	/// </summary>
	/// <param name="X">The mouse's x position.</param>
	/// <param name="Y">The mouse's y position.</param>
	/// /// <param name="Renderer">SDL_Renderer needed to swtich the colour of the text</param>
	void MouseTextUpdate(int X, int Y, SDL_Renderer * Renderer);

	/// <summary>
	/// This method is used to update the colours of the text based on current highlighted text
	/// </summary>
	/// <param name="Renderer">SDL_Renderer needed to swtich the colour of the text</param>
	void KeyboardTextUpdate(SDL_Renderer * Renderer);
};
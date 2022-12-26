#pragma once
#include <map>
#include <list>
#include <string>

#include "ImageObject.h"
#include "TextObject.h"
#include "AnimatedObject.h"
#include "Button.h"


using namespace std;

enum UIText
{
	In,
	Out,
	Plays
};

class ObjectFactory
{
public:

	ObjectFactory(SDL_Renderer* renderer, TTF_Font* textFont);

	void LoadObjects();

	void AnimateObjects(bool isToAnimate);

	void UpdateMouse(bool& isRunning);

	void UpdateObjects();

	void RenderObjects();

	void ChangeUIText(UIText uiEnum, std::string newValue);

	void CleanObjects();


private:
	TTF_Font* gameFont;

	SDL_Color textColor = { 0, 0, 0 };

	SDL_Renderer* gameRenderer;

	Button* button;

	GameObject* backGround;

	list<GameObject*> images;

	map<UIText, TextObject*> TextUI;
};


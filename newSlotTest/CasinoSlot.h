#pragma once
#include "ObjectFactory.h"
#include "Timer.h"

enum GameState 
{
	Stopped,
	Running,
	Paused
};

const float MAX_BAR_TIMER = 1.0f;

class CasinoSlot
{
public:
	~CasinoSlot();

	void loadGameObjects(SDL_Renderer* renderer, TTF_Font* textFont);

	void startGame();

	void UpdateInput(bool& isRunning);

	void UpdateLoop();

	void renderGameObjects();

	void modifyCreditsCounter(bool isCreditsIn);


private:

	int numbelSlot = 0;
	float timerSlot = 0.0f;

	GameState currState = Stopped;
	int CreditsInCounter = 0;
	int CreditsOutCounter = 0;
	int PlaysCounter = 0;

	int loopTime = 5000;

	ObjectFactory* objectFactory = nullptr;
	Timer* timer = nullptr;

};


#include "CasinoSlot.h"

CasinoSlot::~CasinoSlot() 
{
	objectFactory->CleanObjects();

	delete objectFactory;

	delete timer;
}

void CasinoSlot::loadGameObjects(SDL_Renderer* renderer, TTF_Font* textFont)
{
	objectFactory = new ObjectFactory(renderer,textFont);

	timer = new Timer();

	objectFactory->LoadObjects();
}

void CasinoSlot::startGame() 
{
	switch (currState)
	{
	case Stopped:

		if(CreditsInCounter > 0) 
		{
			currState = Running;
			CreditsInCounter--;

			objectFactory->ChangeUIText(In, to_string(CreditsInCounter));
			objectFactory->AnimateObjects(true);

			timer->start();
		}

		break;

	case Running:

		currState = Paused;

		objectFactory->AnimateObjects(false);

		timer->pause();

		break;

	case Paused:

		currState = Running;

		objectFactory->AnimateObjects(true);

		timer->unpause();

		break;

	default:
		break;
	}

	
}

void CasinoSlot::UpdateInput(bool& isRunning)
{
	objectFactory->UpdateMouse(isRunning);
}


void CasinoSlot::UpdateLoop()
{
	if (timer->getTicks() > loopTime)
	{
		printf("Passed the 5 seconds");

		currState = Stopped;

		PlaysCounter++;

		objectFactory->ChangeUIText(Plays, to_string(PlaysCounter));

		objectFactory->AnimateObjects(false);

		timer->stop();
	}

	objectFactory->UpdateObjects();
}

void CasinoSlot::modifyCreditsCounter(bool isCreditsIn)
{
	if(isCreditsIn) 
	{
		CreditsInCounter++;
	}
	else
	{
		CreditsOutCounter += CreditsInCounter;

		objectFactory->ChangeUIText(Out, to_string(CreditsOutCounter));
		CreditsInCounter = 0;
	}

	objectFactory->ChangeUIText(In, to_string(CreditsInCounter));
}

void CasinoSlot::renderGameObjects() 
{
	objectFactory->RenderObjects();
}

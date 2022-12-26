#include "Button.h"
#include "TextureLoader.h"

Button::Button(const char* fileName, int x, int y, int width, int height, SDL_Renderer* renderer)
{

	gameRenderer = renderer;

	objTexture = TextureLoader::LoadTexture(gameRenderer, fileName);

	xPos = x;
	yPos = y;
	objectWidth = width;
	objectHeight = height;

	//srcRect = { 0,0,0,0 };

	destRect = { xPos,yPos,objectWidth,objectHeight };

	loadSpriteSheet(objTexture);

	lastTime = SDL_GetTicks();

}

void Button::Update()
{

	newTime = SDL_GetTicks();
	dt = newTime - lastTime;
	lastTime = newTime;

	timer += dt / 1000;

	if (timer >= MAX_TIMER)
	{
		index = index == 0 ? 1 : 0;
		timer = 0;
	}

}

bool Button::Handle_events(bool& isRunning)
{
    SDL_Event event;

    SDL_PollEvent(&event);

    switch (event.type)
    {

    case SDL_QUIT:
        isRunning = false;

    default:
        break;
    }

	bool rezult = false;

    //The mouse offsets
    int x = 0, y = 0;

    //If a mouse button was pressed
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        //If the left mouse button was pressed
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if ((x > xPos) && (x < xPos + objectWidth) && (y > yPos) && (y < yPos + objectHeight))
            {
				printf("Mouse!!!");
				rezult = true;
                
            }
        }
    }

	return rezult;

}



void Button::Render()
{
	currClip = &buttonClips[index];
	SDL_RenderCopy(gameRenderer, objTexture, currClip, &destRect);
}

void Button::loadSpriteSheet(SDL_Texture* texture)
{
	if (texture == nullptr)
	{
		printf("Invalid Texture!");
		return;
	}

	for (size_t i = 0; i < MAX_CLIPS; i++)
	{
		buttonClips.push_back({});
	}


	int x = 0; 
	int y = 0;

	for (int i = 0; i < MAX_CLIPS; i++)
	{
		buttonClips[i].x = x;
		buttonClips[i].y = y;
		buttonClips[i].w = objectWidth;
		buttonClips[i].h = objectHeight;
		y += objectHeight;
	}
}
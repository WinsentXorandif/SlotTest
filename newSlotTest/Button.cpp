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

void Button::Handle_events()
{
    //The mouse offsets
    int x = 0, y = 0;

    //If the mouse moved
    if (event.type == SDL_MOUSEMOTION)
    {
        //Get the mouse offsets
        x = event.motion.x;
        y = event.motion.y;

        //If the mouse is over the button
        if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
        {
            //Set the button sprite
            clip = &clips[CLIP_MOUSEOVER];
        }
        //If not
        else
        {
            //Set the button sprite
            clip = &clips[CLIP_MOUSEOUT];
        }
    }
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
            if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
            {
                //Set the button sprite
                clip = &clips[CLIP_MOUSEDOWN];
            }
        }
    }
    //If a mouse button was released
    if (event.type == SDL_MOUSEBUTTONUP)
    {
        //If the left mouse button was released
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
            {
                //Set the button sprite
                clip = &clips[CLIP_MOUSEUP];
            }
        }
    }
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
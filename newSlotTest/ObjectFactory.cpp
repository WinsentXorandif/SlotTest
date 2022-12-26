#include "ObjectFactory.h"
#include <typeinfo>


ObjectFactory::ObjectFactory(SDL_Renderer* renderer, TTF_Font* font)
{
	gameFont = font;
    gameRenderer = renderer;
}

void ObjectFactory::LoadObjects()
{
    TextUI.insert({ In, new TextObject("Credits In: ", 10, 20, 150, 50, textColor, gameFont,gameRenderer) });

    TextUI.insert({ Out, new TextObject("Credits Out: ", 590, 20, 150, 50, textColor, gameFont,gameRenderer) });

    TextUI.insert({ Plays, new TextObject("Plays: ", 750, 450, 150, 50, textColor, gameFont,gameRenderer) });

    //-----------------------

    //images.push_back(new ImageObject("newSlotTest/Resources/Images/slots.png", 150, 150, 500, 350, gameRenderer));

    //images.push_back(new ImageObject("newSlotTest/Resources/Images/PressSpace.png", 200, 500, 400, 50, gameRenderer));

    //images.push_back(new ImageObject("newSlotTest/Resources/Images/RightShift.png", 590, 75, 200, 50, gameRenderer));

    //images.push_back(new ImageObject("newSlotTest/Resources/Images/LeftShift.png", 10, 75, 200, 50, gameRenderer));

    //images.push_back(new AnimatedObject("newSlotTest/Resources/Images/SS64.png", 220, 300, 64, 64, 50,15, gameRenderer));

    //images.push_back(new AnimatedObject("newSlotTest/Resources/Images/SS64.png", 370, 300, 64, 64, 50, 15, gameRenderer));

    //images.push_back(new AnimatedObject("newSlotTest/Resources/Images/SS64.png", 510, 300, 64, 64, 50, 15, gameRenderer));

    maxSpriteClips = 14;

    images.push_back(new AnimatedObject("newSlotTest/Resources/Images/spriteall3.png", 190, 200, 100, 100, 14, 14, gameRenderer));
 //   images.push_back(new AnimatedObject("newSlotTest/Resources/Images/spriteall3.png", 300, 200, 100, 100, 50, 14, gameRenderer));
 //   images.push_back(new AnimatedObject("newSlotTest/Resources/Images/spriteall3.png", 410, 200, 100, 100, 50, 14, gameRenderer));
 //   images.push_back(new AnimatedObject("newSlotTest/Resources/Images/spriteall3.png", 520, 200, 100, 100, 50, 14, gameRenderer));
 //   images.push_back(new AnimatedObject("newSlotTest/Resources/Images/spriteall3.png", 630, 200, 100, 100, 50, 14, gameRenderer));
    
    images.push_back(new AnimatedObject("newSlotTest/Resources/Images/spriteall3.png", 190, 310, 100, 100, 14, 14, gameRenderer));
//    images.push_back(new AnimatedObject("newSlotTest/Resources/Images/spriteall3.png", 300, 310, 100, 100, 50, 14, gameRenderer));
//    images.push_back(new AnimatedObject("newSlotTest/Resources/Images/spriteall3.png", 410, 310, 100, 100, 50, 14, gameRenderer));
//    images.push_back(new AnimatedObject("newSlotTest/Resources/Images/spriteall3.png", 520, 310, 100, 100, 50, 14, gameRenderer));
//    images.push_back(new AnimatedObject("newSlotTest/Resources/Images/spriteall3.png", 630, 310, 100, 100, 50, 14, gameRenderer));

    images.push_back(new AnimatedObject("newSlotTest/Resources/Images/spriteall3.png", 190, 420, 100, 100, 14, 14, gameRenderer));
//    images.push_back(new AnimatedObject("newSlotTest/Resources/Images/spriteall3.png", 300, 420, 100, 100, 50, 14, gameRenderer));
//    images.push_back(new AnimatedObject("newSlotTest/Resources/Images/spriteall3.png", 410, 420, 100, 100, 50, 14, gameRenderer));
//    images.push_back(new AnimatedObject("newSlotTest/Resources/Images/spriteall3.png", 520, 420, 100, 100, 50, 14, gameRenderer));
//    images.push_back(new AnimatedObject("newSlotTest/Resources/Images/spriteall3.png", 630, 420, 100, 100, 50, 14, gameRenderer));
    

    backGround = new ImageObject("newSlotTest/Resources/Images/background2.png", 0, 0, 1280, 800, gameRenderer);

    button = new Button("newSlotTest/Resources/Images/start33.png", 900, 280, 256, 115, gameRenderer);



}

void ObjectFactory::AnimateObjects(bool isAnimate) 
{
    for (auto const& image : images)
    {
        AnimatedObject* animatedObj = dynamic_cast<AnimatedObject*>(image);

        if(animatedObj != nullptr) 
        {
 
            animatedObj->Animate(isAnimate);
        }
    }
}


bool ObjectFactory::UpdateMouse(bool& isRunning)
{
    return button->Handle_events(isRunning);
}


void ObjectFactory::UpdateObjects()
{
    button->Update();
}



void ObjectFactory::ChangeUIText(UIText uiText,std::string stringValue) 
{
    TextUI.at(uiText)->ChangeText(stringValue);
}

void ObjectFactory::RenderObjects()
{

    backGround->Render();

    for (auto const& ui : TextUI)
    {
        ui.second->Render();
    }

    for(auto const& image : images) 
    {
        image->Render(index);
        index++;
        index = index >= maxSpriteClips ? 0 : index;
    }

    button->Render();
}

void ObjectFactory::CleanObjects()
{
    for (auto const& ui : TextUI)
    {
        delete ui.second;
    }

    for(auto const& image : images) 
    {
        delete image;
    }

    delete backGround;
    delete button;

    TextUI.clear();

    images.clear();
}
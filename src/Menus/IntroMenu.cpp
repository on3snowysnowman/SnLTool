#include "IntroMenu.h"
#include "MenuHandler.h"


// Constructors / Deconstructor

IntroMenu::IntroMenu(Sprite* _logo) : Menu("Intro")
{
    logo = _logo;

    lsdc.content.push_back(ColorString("Load Save", "White"));
    lsdc.content.push_back(ColorString("Create Save", "White"));
}


// Public

void IntroMenu::start() 
{
    lsdc.reset();
}

void IntroMenu::update()
{
    window->set_cursor_position(29, 3);
    window->add_sprite_at_cursor_pos(logo);

    if(input_handler->is_key_pressed(SDLK_RETURN)) 
    {
        deactivate_menu();
        input_handler->block_key_until_released(SDLK_RETURN);
        MenuHandler::activate_menu("Main");
    }
}


// Private

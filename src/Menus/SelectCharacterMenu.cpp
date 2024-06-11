#include "MenuHandler.h"

#include "SelectCharacterMenu.h"


// Constructors / Deconstructor

SelectCharacterMenu::SelectCharacterMenu(Character** _focused_character, 
    std::vector<Character*>* _all_characters) : Menu("SelectCharacter")
{
    focused_character = _focused_character;
    all_characters = _all_characters;
} 


// Public

void SelectCharacterMenu::start() 
{
    lsdc.reset();
    lsdc.content.clear();

    for(Character* c : *all_characters)
    {
        lsdc.content.push_back(ColorString(c->name, "White"));
    }

    lsdc.content.push_back(ColorString("<-- ", "Red"));
}

#include <iostream>

void SelectCharacterMenu::update() 
{
    window->add_str("[...][ Character Save Type Selection /"
        " Select Character ]\n\n");

    menu_tools->simulate_list_selection(lsdc);

    if(!lsdc.item_has_been_selected) return;

    lsdc.item_has_been_selected = false;

    // Back button selected
    if(lsdc.cursor_pos == lsdc.content.size() - 1) 
    {
        deactivate_menu();
        input_handler->block_key_until_released(SDLK_RETURN);
        return;
    }
    (*focused_character) = all_characters->at(lsdc.cursor_pos);
    
    MenuHandler::activate_menu("Simulation");
    
    input_handler->block_key_until_released(SDLK_RETURN);
}


// Private

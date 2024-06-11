#include "EventSystem.h"

#include "CharacterSaveTypeSelectionMenu.h"
#include "MenuHandler.h"

// Constructors / Deconstructor 

CharacterSaveTypeSelectionMenu::CharacterSaveTypeSelectionMenu() : 
    Menu("CharacterSaveTypeSelection") 
{
    lsdc.cursor_color = "Blue";

    lsdc.content.push_back(ColorString("Create New Character", "White"));
    lsdc.content.push_back(ColorString("Select Character", "White"));
    lsdc.content.push_back(ColorString("Exit Save", "Red"));
}


// Public

void CharacterSaveTypeSelectionMenu::start() { lsdc.reset(); }

void CharacterSaveTypeSelectionMenu::update() 
{
    window->add_str("[...][ Character Save Type Selection ]\n\n");
    // window->add_str("-- Make a Selection --\n\n");

    menu_tools->simulate_list_selection(lsdc);

    if(!lsdc.item_has_been_selected) return;

    lsdc.item_has_been_selected = false;

    std::string& selected_string = lsdc.content.at(lsdc.cursor_pos).content;

    if(selected_string == "Create New Character")
    {
        MenuHandler::activate_menu("CreateCharacter");
    }

    else if(selected_string == "Select Character")
    {
        MenuHandler::activate_menu("SelectCharacter");
    }

    else if(selected_string == "Exit Save")
    {
        CallbackManager::trigger_callback("save_characters");
        input_handler->block_key_until_released(SDLK_RETURN);
        deactivate_menu();
    }
}


// Private


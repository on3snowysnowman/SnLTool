#include "MenuHandler.h"
#include "EventSystem.h"

#include "MainMenu.h"


// Constructors / Deconstructor

MainMenu::MainMenu() : Menu("Main") 
{
    lsdc.content.push_back(ColorString("Load Save", "White"));
    lsdc.content.push_back(ColorString("Create New Save", "White"));
    lsdc.content.push_back(ColorString("Delete Save", "White"));
    lsdc.content.push_back(ColorString("Add Spell", "Purple"));
    lsdc.content.push_back(ColorString("Add Potion", "Purple"));
    lsdc.content.push_back(ColorString("Quit", "Red"));
}


// Public

void MainMenu::start() { lsdc.reset(); }

void MainMenu::update() 
{
    window->add_str("[ Main Menu ]\n\n");

    menu_tools->simulate_list_selection(lsdc);

    if(!lsdc.item_has_been_selected) return;

    lsdc.item_has_been_selected = false;

    const std::string& selected_item = lsdc.get_selected_item();

    if(selected_item == "Load Save") 
    {
        MenuHandler::activate_menu("SaveLoad");
        return;
    }

    else if(selected_item == "Create New Save")
    {
        MenuHandler::activate_menu("CreateSave");
        return;
    }

    else if(selected_item == "Delete Save")
    {
        MenuHandler::activate_menu("DeleteSave");
        return;
    }

    else if(selected_item == "Add Spell")
    {
        MenuHandler::activate_menu("AddSpell");
        return;
    }

    else if(selected_item == "Add Potion")
    {
        MenuHandler::activate_menu("AddPotion");
        return;
    }

    // else: selected_item == "Quit"
    CallbackManager::trigger_callback("quit");
}


// Private

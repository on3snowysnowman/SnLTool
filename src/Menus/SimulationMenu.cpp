#include "MenuHandler.h"
#include "EventSystem.h"

#include "SimulationMenu.h"


// Constructors / Deconstructor

SimulationMenu::SimulationMenu(Character** _focused_character) : 
    Menu("Simulation")
{
    focused_character = _focused_character;

    lsdc.content.push_back(ColorString("Modify Hitpoints & Mana", "White"));
    lsdc.content.push_back(ColorString("View Full Stats", "White"));
    lsdc.content.push_back(ColorString("<-- Select Different Character", "Orange"));
    lsdc.content.push_back(ColorString("Quit", "Red"));
}


// Public

void SimulationMenu::start() 
{
    lsdc.reset();
}

void SimulationMenu::update() 
{
    window->add_str("[...][...][ Simulation Menu ]\n\n");

    menu_tools->simulate_list_selection(lsdc);

    render_character_stats();

    if(!lsdc.item_has_been_selected) return;

    lsdc.item_has_been_selected = false;

    const std::string& selected_item = 
        lsdc.get_selected_item();
    
    if(selected_item == "Modify Hitpoints & Mana")
    {
        MenuHandler::activate_menu("ModifyHitpointMana");
    }

    else if(selected_item == "View Full Stats")
    {
        MenuHandler::activate_menu("ViewStats");
    }

    else if(selected_item == "<-- Select Different Character")
    {
        deactivate_menu();
        input_handler->block_key_until_released(SDLK_RETURN);
    }

    // else: selected_item == "Quit"
    else
    {
        CallbackManager::trigger_callback("save_characters");
        CallbackManager::trigger_callback("quit");
    }
}


// Private

void SimulationMenu::render_character_stats()
{
    window->set_cursor_position(40, 2);
    window->set_anchor(40);

    window->add_str("Name: " +  (*focused_character)->name + '\n');
    window->add_str("Hitpoints: ");
    menu_tools->render_multi_colored_meter((*focused_character)->hitpoints, 
        0, (*focused_character)->max_hitpoints);
    window->add_str("\nMana: ");
    menu_tools->render_single_color_meter((*focused_character)->mana, 0, 
        (*focused_character)->max_mana, "Blue");
}

#include "MenuHandler.h"
#include "EventSystem.h"
#include "LSDLE.h"

#include "SimulationMenu.h"


// Constructors / Deconstructor

SimulationMenu::SimulationMenu(Character** _focused_character) : 
    Menu("Simulation")
{
    focused_character = _focused_character;

    int screen_width = LSDLE::get_screen_width();
    int screen_height = LSDLE::get_screen_height();

    window->resize_window(0, 0, screen_width * 0.45, screen_height);

    first_stats_window = new Window(screen_width * 0.48, 0, screen_width * 0.75, 
        screen_height);
    second_stats_window = new Window(screen_width * 0.78, 0, screen_width, 
        screen_height);

    first_stats_menu_tools = new MenuTools(first_stats_window);
    second_stats_menu_tools = new MenuTools(second_stats_window);

    lsdc.content.push_back(ColorString("Modify Hitpoints & Mana", "White"));
    lsdc.content.push_back(ColorString("View Inventory", "White"));
    lsdc.content.push_back(ColorString("Edit Character", "White"));
    lsdc.content.push_back(ColorString("<-- Select Different Character", "Orange"));
    lsdc.content.push_back(ColorString("Quit", "Red"));
}


// Public

void SimulationMenu::start() 
{
    target_stat_render_function = &SimulationMenu::render_first_page_stats;
    lsdc.reset();
}

void SimulationMenu::update() 
{
    window->add_str("[...][...][ Simulation Menu ]\n\n");

    menu_tools->simulate_list_selection(lsdc);

    (this->*target_stat_render_function)();

    if(!lsdc.item_has_been_selected) return;

    lsdc.item_has_been_selected = false;

    const std::string& selected_item = 
        lsdc.get_selected_item();
    
    if(selected_item == "Modify Hitpoints & Mana")
    {
        MenuHandler::activate_menu("ModifyHitpointMana");
    }

    else if(selected_item == "View Inventory")
    {
        MenuHandler::activate_menu("ViewInventory");
    }

    else if(selected_item == "Edit Character")
    {
        MenuHandler::activate_menu("EditStats");
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

void SimulationMenu::render_first_page_stats() 
{
    first_stats_window->add_str("[Page 1 / 2]\n\n -- Stats --\n\n");
    first_stats_window->add_str("Name: ", "LightGray");
    first_stats_window->add_str((*focused_character)->name + '\n');
    first_stats_window->add_str("Hitpoints: ", "LightGray");
    first_stats_menu_tools->render_multi_colored_meter((*focused_character)->hitpoints, 
        0, (*focused_character)->max_hitpoints);
    first_stats_window->add_str("\nMana: ", "LightGray");
    first_stats_menu_tools->render_single_color_meter((*focused_character)->mana, 0, 
        (*focused_character)->max_mana, "Blue");
    first_stats_window->add_str("\nRace: ", "LightGray");
    first_stats_window->add_str((*focused_character)->race);
    first_stats_window->add_str("\nHeight: ", "LightGray");
    first_stats_window->add_str((*focused_character)->height);
    first_stats_window->add_str("\nWeight: ", "LightGray");
    first_stats_window->add_str((*focused_character)->weight);
    first_stats_window->add_str("\nSpeed: ", "LightGray");
    first_stats_window->add_str((*focused_character)->speed);
    first_stats_window->add_str("\n\nDescription: ", "LightGray");
    first_stats_window->add_str((*focused_character)->description);

    second_stats_window->add_str("\n\n -- Skills --\n\n");
    second_stats_window->add_str("Alchemy: ", "LightGray");
    second_stats_menu_tools->render_colored_number((*focused_character)->skills.at(0), 
        0, 10);
    second_stats_window->add_str("\nAnimal handling: ", "LightGray");
    second_stats_menu_tools->render_colored_number((*focused_character)->skills.at(1), 
        0, 10);
    second_stats_window->add_str("\nAppraising: ", "LightGray");
    second_stats_menu_tools->render_colored_number((*focused_character)->skills.at(2), 
        0, 10);
    second_stats_window->add_str("\nArcanary: ", "LightGray");
    second_stats_menu_tools->render_colored_number((*focused_character)->skills.at(3), 
        0, 10);
    second_stats_window->add_str("\nAthletics: ", "LightGray");
    second_stats_menu_tools->render_colored_number((*focused_character)->skills.at(4),  
        0, 10);
    second_stats_window->add_str("\nCooking: ", "LightGray");
    second_stats_menu_tools->render_colored_number((*focused_character)->skills.at(5), 
        0, 10);
    second_stats_window->add_str("\nIntelligence: ", "LightGray");
    second_stats_menu_tools->render_colored_number((*focused_character)->skills.at(6), 
        0, 10);
    second_stats_window->add_str("\nMedicine: ", "LightGray");
    second_stats_menu_tools->render_colored_number((*focused_character)->skills.at(7), 
        0, 10);
    second_stats_window->add_str("\nPerception: ", "LightGray");
    second_stats_menu_tools->render_colored_number((*focused_character)->skills.at(8), 
        0, 10);
    second_stats_window->add_str("\nSpeech: ", "LightGray");
    second_stats_menu_tools->render_colored_number((*focused_character)->skills.at(9), 
        0, 10);
    second_stats_window->add_str("\nStealth: ", "LightGray");
    second_stats_menu_tools->render_colored_number((*focused_character)->skills.at(10), 
        0, 10);
    second_stats_window->add_str("\nStrength: ", "LightGray");
    second_stats_menu_tools->render_colored_number((*focused_character)->skills.at(11), 
        0, 10);
    second_stats_window->add_str("\nSurvival: ", "LightGray");
    second_stats_menu_tools->render_colored_number((*focused_character)->skills.at(12), 
        0, 10);
    second_stats_window->add_str("\nSlight of Hand: ", "LightGray");
    second_stats_menu_tools->render_colored_number((*focused_character)->skills.at(13), 
        0, 10);

    if(input_handler->is_key_pressed_and_available(SDLK_RIGHT))
    {
        target_stat_render_function = &SimulationMenu::render_second_page_stats;
        input_handler->set_delay(SDLK_RIGHT);
    }
}

void SimulationMenu::render_second_page_stats() 
{
    first_stats_window->add_str("[Page 2 / 2]\n\n");

    first_stats_window->add_str(" -- Attributes --\n\n");

    for(const std::string& _str : (*focused_character)->attributes)
    {
        first_stats_window->add_str(_str + '\n');
    }

    second_stats_window->add_str("\n\n -- Effects --\n\n");

    for(const std::string& _str : (*focused_character)->effects)
    {
        second_stats_window->add_str(_str + '\n');
    }

    if(input_handler->is_key_pressed_and_available(SDLK_LEFT))
    {
        target_stat_render_function = &SimulationMenu::render_first_page_stats;
        input_handler->set_delay(SDLK_LEFT);
    }
}

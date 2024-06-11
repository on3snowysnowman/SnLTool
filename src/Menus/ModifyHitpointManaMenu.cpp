#include "LStringManip.h"
#include "LMath.h"
#include "EventSystem.h"

#include "ModifyHitpointManaMenu.h"


// Constructors / Deconstructor

ModifyHitpointManaMenu::ModifyHitpointManaMenu(Character** _focused_character)
    : Menu("ModifyHitpointMana")
{
    focused_character = _focused_character;

    modification_choice = new MenuToolChoice(window, "Blue", "What to Modify", 
        0);
    modification_choice->choices.push_back(ColorString("Hitpoints", "Green"));
    modification_choice->choices.push_back(ColorString("Mana", "Blue"));

    modification_amount = new MenuToolVariable(window, MenuToolItem::INT, 
        "Blue", "Amount", "1");

    increase_button = new MenuToolButton<ModifyHitpointManaMenu>(this, 
        handle_increase, window, "Increase", "Blue", "Green");

    decrease_button = new MenuToolButton<ModifyHitpointManaMenu>(this, 
        handle_decrease, window, "Decrease", "Blue", "Red");

    back_button = new MenuToolButton<ModifyHitpointManaMenu>(this,
        exit_menu, window, "<--", "Blue", "Red");

    msdc.fill_content({modification_choice, modification_amount, 
        increase_button, decrease_button, back_button});

    msdc.block_enter_key = false;
}


// Public

void ModifyHitpointManaMenu::start() 
{
    msdc.reset();
}

void ModifyHitpointManaMenu::update() 
{
    window->add_str("[...][...][ Simulation Menu / Modify Hitpoints & Mana ]"
        "\n\n");

    menu_tools->simulate_menu(msdc);

    render_character_stats();
}


// Private

void ModifyHitpointManaMenu::render_character_stats()
{
    window->set_cursor_position(40, 2);
    window->set_anchor(40);

    window->add_str((*focused_character)->name + '\n');
    window->add_str("Hitpoints: ");
    menu_tools->render_multi_colored_meter((*focused_character)->hitpoints, 
        0, (*focused_character)->max_hitpoints);
    window->add_str("\nMana: ");
    menu_tools->render_single_color_meter((*focused_character)->mana, 0, 
        (*focused_character)->max_mana, "Blue");
}

void ModifyHitpointManaMenu::handle_increase() 
{
    int* modification_target {};
    int* modification_target_max {};

    if(modification_choice->get_choice() == "Hitpoints")
    {
        modification_target = &(*focused_character)->hitpoints;
        modification_target_max = &(*focused_character)->max_hitpoints;
    }

    else 
    {
        modification_target = &(*focused_character)->mana;
        modification_target_max = &(*focused_character)->max_mana;
    }

    // Add the modification amount to the character's hitpoints, then round it
    // down to their maximum if it exceeds it

    *modification_target = LSDLELIB::round_num_to_maximum(
        LSDLELIB::handle_int32_addition(*modification_target,
        LSDLELIB::string_to_int32(modification_amount->content)),
        *modification_target_max);
    
    input_handler->set_delay(SDLK_RETURN, 8);
}

void ModifyHitpointManaMenu::handle_decrease() 
{
    int* modification_target {};
    int* modification_target_max {};

    if(modification_choice->get_choice() == "Hitpoints")
    {
        modification_target = &(*focused_character)->hitpoints;
        modification_target_max = &(*focused_character)->max_hitpoints;
    }

    else 
    {
        modification_target = &(*focused_character)->mana;
        modification_target_max = &(*focused_character)->max_mana;
    }

    // Subtract the modification amount from the character's hitpoints, then 
    // round it up to zero if it dips below

    *modification_target = LSDLELIB::round_num_to_minimum(
        LSDLELIB::handle_int32_addition(*modification_target,
        -LSDLELIB::string_to_int32(modification_amount->content)),
        0);

    input_handler->set_delay(SDLK_RETURN, 8);
}

void ModifyHitpointManaMenu::exit_menu()
{
    CallbackManager::trigger_callback("save_characters");
    deactivate_menu();
    input_handler->block_key_until_released(SDLK_RETURN);
}

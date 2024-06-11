#include "JsonLoader.h"

#include "AddPotionMenu.h"


// Constructors / Deconstructor

AddPotionMenu::AddPotionMenu() : Menu("AddPotion")
{
    name = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", "Name");
    description = new MenuToolVariable(window, MenuToolItem::STRING, "Blue",
        "Description");
    ingredients = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", 
        "Ingredients");

    add_button = new MenuToolButton<AddPotionMenu>(this, handle_add_potion,
        window, "Add", "Blue", "Green");
    cancel_button = new MenuToolButton<AddPotionMenu>(this, exit_menu, window,
        "Cancel", "Blue", "Red");

    msdc.fill_content({name, description, ingredients, add_button, 
        cancel_button});
}


// Public

void AddPotionMenu::start() 
{
    msdc.reset();

    name->content.clear();
    description->content.clear();
    ingredients->content.clear();
}

void AddPotionMenu::update() 
{
    window->add_str("[ Main Menu / Add Potion ]\n\n");
    
    menu_tools->simulate_menu(msdc);
}


// Private

void AddPotionMenu::handle_add_potion() 
{
    // If crucial data was left unfilled
    if(name->content.size() == 0 || 
        description->content.size() == 0 || 
        ingredients->content.size() == 0) return;

    // Full list of potions
    Json all_potions = JsonLoader::get(POTIONS_PATH.c_str());

    Json new_potion;

    new_potion["name"] = name->content;
    new_potion["description"] = description->content;
    new_potion["ingredients"] = ingredients->content;

    all_potions.push_back(new_potion);

    // Add the full potions with the new potion back to the potions file
    JsonLoader::dump(all_potions, POTIONS_PATH.c_str());

    exit_menu();
}

void AddPotionMenu::exit_menu() 
{
    deactivate_menu();
    input_handler->block_key_until_released(SDLK_RETURN);
}

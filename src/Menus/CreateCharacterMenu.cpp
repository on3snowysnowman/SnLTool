#include "LStringManip.h"

#include "CreateCharacterMenu.h"

// Constructors / Deconstructor

CreateCharacterMenu::CreateCharacterMenu(
    std::vector<Character*>* _all_characters) : Menu("CreateCharacter")
{
    all_characters = _all_characters;

    name = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", "Name");
    race = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", "Race");
    max_hitpoints = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Max Hitpoints");
    max_mana = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Max Mana");

    create_button = new MenuToolButton<CreateCharacterMenu>(this, 
        create_character, window, "Create", "Blue", "Green");
    cancel_button = new MenuToolButton<CreateCharacterMenu>(this, 
        exit_menu, window, "Cancel", "Blue", "Red");

    msdc.fill_content({name, race, max_hitpoints, max_mana, create_button, 
        cancel_button});
}


// Public

void CreateCharacterMenu::start() 
{
    msdc.reset();

    name->content.clear();
    race->content.clear();
    max_hitpoints->content = "0";
    max_mana->content = "0";
}

void CreateCharacterMenu::update() 
{
    window->add_str("[...][ Character Save Type Selection"
    " / Create Character ]\n\n");

    menu_tools->simulate_menu(msdc);
}


// Private

void CreateCharacterMenu::create_character()
{
    if(name->content.size() == 0 || 
        race->content.size() == 0) return;

    Character* new_c = new Character;
    
    new_c->name = name->content;
    new_c->race = race->content;

    new_c->max_hitpoints = LSDLELIB::string_to_int32(max_hitpoints->content);
    new_c->hitpoints = new_c->max_hitpoints;

    new_c->max_mana = LSDLELIB::string_to_int32(max_mana->content);
    new_c->mana = new_c->max_mana;

    all_characters->push_back(new_c);

    exit_menu();
}

void CreateCharacterMenu::exit_menu()
{
    deactivate_menu();
    input_handler->block_key_until_released(SDLK_RETURN);
}

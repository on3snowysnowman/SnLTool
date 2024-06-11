#include "JsonLoader.h"
#include "LStringManip.h"

#include "AddSpellMenu.h"


// Constructors / Deconstructor

AddSpellMenu::AddSpellMenu() : Menu("AddSpell") 
{
    name = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", "Name", 
        "");
    description = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", 
        "Description", "");
    arcanary_level = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Arcanary Level", "");
    mana_cost = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Mana Cost", "");
    casting_time = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", 
        "Casting Time", "");
    range = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", "Range", 
        "");
    duration = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", 
        "Duration", "");
    damage = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", 
        "Damage", "");
    per_level_increase = new MenuToolVariable(window, MenuToolItem::STRING, 
        "Blue", "Per Level Increase", "");
    upgrades = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", 
        "Upgrades", "");

    add_button = new MenuToolButton<AddSpellMenu>(this, handle_add_spell, 
        window, "Add", "Blue", "Green");
    cancel_button = new MenuToolButton<AddSpellMenu>(this, exit_menu, window,
        "Cancel", "Blue", "Red");

    msdc.fill_content({name, description, arcanary_level, mana_cost, 
        casting_time, range, duration, damage, per_level_increase, upgrades,
        add_button, cancel_button});
}


// Public

void AddSpellMenu::start() 
{
    msdc.reset();
    name->content.clear();
    description->content.clear();
    arcanary_level->content.clear();
    mana_cost->content.clear();
    casting_time->content.clear();
    range->content.clear();
    duration->content.clear();
    damage->content.clear();
    per_level_increase->content.clear();
    upgrades->content.clear();
}

void AddSpellMenu::update() 
{
    window->add_str("[ Main Menu / Add Spell ]\n\n");

    menu_tools->simulate_menu(msdc);
}


// Private

void AddSpellMenu::handle_add_spell() 
{
    if(name->content.size() == 0 ||
        description->content.size() == 0 ||
        casting_time->content.size() == 0 ||
        range->content.size() == 0 ||
        duration->content.size() == 0)
    {
        return;
    }

    // Get the spells
    Json all_spells = JsonLoader::get(SPELLS_PATH.c_str());
    Json new_spell;

    // Create a new spell
    new_spell["name"] = name->content;
    new_spell["description"] = description->content;
    new_spell["arcanary_level"] = LSDLELIB::string_to_uint8(
        arcanary_level->content);
    new_spell["mana_cost"] = LSDLELIB::string_to_uint16(
        mana_cost->content);
    new_spell["casting_time"] = casting_time->content;
    new_spell["range"] = range->content;
    new_spell["duration"] = duration->content;
    new_spell["damage"] = damage->content;
    new_spell["per_level_increase"] = per_level_increase->content;
    new_spell["upgrades"] = upgrades->content;

    // Add the new spell to the spells
    all_spells.push_back(new_spell);

    // Save the spells to the spells file
    JsonLoader::dump(all_spells, SPELLS_PATH.c_str());

    exit_menu();
}

void AddSpellMenu::exit_menu()
{
    input_handler->block_key_until_released(SDLK_RETURN);
    deactivate_menu();
}

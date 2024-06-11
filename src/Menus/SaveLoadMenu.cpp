#include "LStringManip.h"
#include "MenuHandler.h"

#include "SaveLoadMenu.h"


// Constructors / Deconstructor

SaveLoadMenu::SaveLoadMenu(SaveHandler* _save_handler, 
    std::vector<Character*>* _all_characters) : Menu("SaveLoad")
{
    save_handler = _save_handler;

    all_characters = _all_characters;
}


// Public

void SaveLoadMenu::start() 
{
    lsdc.reset();

    fetch_saves_on_disk();
}

void SaveLoadMenu::update() 
{
    window->add_str("[ Main Menu / Load Save ]\n\n");

    menu_tools->simulate_list_selection(lsdc);

    if(!lsdc.item_has_been_selected) return;

    lsdc.item_has_been_selected = false;

    // Back button was pressed
    if(lsdc.cursor_pos == lsdc.content.size() - 1) 
    {
        input_handler->block_key_until_released(SDLK_RETURN);
        deactivate_menu();
        return;
    }

    // Load the characters from the save path. The cursor position is 
    // used here, because the position of the cursor is directly equal to
    // the position inside the save handler's save paths. So simply tell the
    // save handler to get the characters at the save path of the cursor's 
    // position.
    *all_characters = save_handler->load_characters_from_save(
        save_handler->get_saves().at(lsdc.cursor_pos));

    deactivate_menu();
    MenuHandler::activate_menu("CharacterSaveTypeSelection");
}


// Private

void SaveLoadMenu::fetch_saves_on_disk()
{
    lsdc.content.clear();

    for(const std::string& str : save_handler->get_saves())
    {
        lsdc.content.push_back(
            ColorString(LSDLELIB::get_str_after_char_from_end(str, '\\'),
            "White"));
    }

    lsdc.content.push_back(ColorString("<--", "Red"));
}

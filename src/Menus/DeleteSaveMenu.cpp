#include "LStringManip.h"

#include "DeleteSaveMenu.h"


// Constructors / Deconstructor

DeleteSaveMenu::DeleteSaveMenu(SaveHandler* _save_handler) : 
    Menu("DeleteSave") 
{
    save_handler = _save_handler;

    confirm_deletion_lsdc.content.push_back(ColorString("Yes", "Green"));
    confirm_deletion_lsdc.content.push_back(ColorString("No", "Red"));
}


// Public

void DeleteSaveMenu::start() 
{
    target_function = &DeleteSaveMenu::main_update_function;

    lsdc.reset();
    lsdc.content.clear();

    // Reset to 1, so the default option is "No"
    confirm_deletion_lsdc.cursor_pos = 1;

    for(const std::string& str : save_handler->get_saves())
    {
        lsdc.content.push_back(
            ColorString(LSDLELIB::get_str_after_char_from_end(str, '\\'), 
            "White"));
    }

    lsdc.content.push_back(ColorString("<--", "Red"));
}

void DeleteSaveMenu::update() 
{
    (this->*target_function)();
}


// Private

void DeleteSaveMenu::main_update_function() 
{
    window->add_str("[ Main Menu / Delete Save ]\n\n");
    
    menu_tools->simulate_list_selection(lsdc);

    if(!lsdc.item_has_been_selected) return;

    lsdc.item_has_been_selected = false;

    // Back button was pressed
    if(lsdc.cursor_pos == lsdc.content.size() - 1)
    {
        deactivate_menu();
        input_handler->block_key_until_released(SDLK_RETURN);
        return;
    }

    // A path was selected to be deleted

    target_function = &DeleteSaveMenu::confirm_save_deletion_update_function;
}

void DeleteSaveMenu::confirm_save_deletion_update_function()
{
    window->add_str("\nAre you SURE you want to delete this save?\n\nThis "
        "action can ");
    window->add_str("NOT ", "Red");
    window->add_str("be undone.\n\n-- Make a Selection --\n\n");

    menu_tools->simulate_list_selection(confirm_deletion_lsdc);

    if(!confirm_deletion_lsdc.item_has_been_selected) return;

    confirm_deletion_lsdc.item_has_been_selected = false;

    if(confirm_deletion_lsdc.get_selected_item() == "No") 
    {
        start();
        input_handler->block_key_until_released(SDLK_RETURN);
        return;
    }

    save_handler->delete_save_from_disk(
        save_handler->get_saves().at(lsdc.cursor_pos));
    start();
    deactivate_menu();
    input_handler->block_key_until_released(SDLK_RETURN);
}

#include "MenuHandler.h"

#include "CreateSaveMenu.h"


// Constructors / Deconstructor

CreateSaveMenu::CreateSaveMenu(SaveHandler* _save_handler) : 
    Menu("CreateSave")
{
    save_handler = _save_handler;

    save_name = new MenuToolVariable(window, MenuToolItem::STRING, "Blue",
        "Save Name");

    cancel_button = new MenuToolButton<CreateSaveMenu>(this, exit_menu, window,
        "Cancel", "Blue", "Red");
    create_button = new MenuToolButton<CreateSaveMenu>(this, 
        handle_save_creation, window, "Create", "Blue", "Green");

    msdc.fill_content({save_name, create_button, cancel_button});
}


// Public

void CreateSaveMenu::start() 
{
    target_function = &CreateSaveMenu::main_update_function;
    msdc.reset();
    save_name->content.clear();
}

void CreateSaveMenu::update() 
{
    // Call the target update function
    (this->*target_function)();
}


// Private

void CreateSaveMenu::main_update_function() 
{
    window->add_str("[ Main Menu / Create Save ]\n\n");

    menu_tools->simulate_menu(msdc);
}

void CreateSaveMenu::creation_failed_update_function() 
{
    window->add_str("\nThis save file name already exists. Pick a different "
        "one or delete the old save.\n\nPress Enter to continue...");
    
    if(input_handler->is_key_pressed_and_available(SDLK_RETURN))
    {
        start();
        input_handler->block_key_until_released(SDLK_RETURN);
    }
}

void CreateSaveMenu::handle_save_creation() 
{
    if(save_name->content.size() == 0) return;

    // Target path already exist for the name of this save
    if(!save_handler->create_new_save_file_on_disk(save_name->content))
    { 
        input_handler->block_key_until_released(SDLK_RETURN);

        // Switch the target update function to the failed update function
        target_function = &CreateSaveMenu::creation_failed_update_function; 
        return;
    }
    
    exit_menu();
    MenuHandler::activate_menu("CharacterSaveTypeSelection");
}

void CreateSaveMenu::exit_menu() 
{
    deactivate_menu();
    input_handler->block_key_until_released(SDLK_RETURN);
}

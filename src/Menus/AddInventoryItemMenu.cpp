#include "LStringManip.h"

#include "AddInventoryItemMenu.h"

// Constructors / Deconstructor

AddInventoryItemMenu::AddInventoryItemMenu(Character** _focused_character) : 
    Menu("AddInventoryItem")
{
    focused_character = _focused_character;

    name = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", "Name");
    amount = new MenuToolVariable(window, MenuToolItem::INT, "Blue", "Amount to Add", "", "1");

    attributes = new MenuToolTextList(window, "Blue", "Attributes");
    
    add_button = new MenuToolButton<AddInventoryItemMenu>(this, handle_add_item, window, "Add",
        "Blue", "Green");
    cancel_button = new MenuToolButton<AddInventoryItemMenu>(this, exit_menu, window, "Cancel",
        "Blue", "Red");

    msdc.fill_content({name, attributes, amount, add_button, cancel_button});
}


// Public

void AddInventoryItemMenu::start() 
{
    msdc.reset();
    msdc.reset_contents();
}

void AddInventoryItemMenu::update() 
{
    window->add_str("[...][...][ Simulation Menu / View Inventory / Add Item ]\n\n");

    menu_tools->simulate_menu(msdc);
}


// Private

void AddInventoryItemMenu::handle_add_item() 
{
    // Get the amount to add of this item. 
    uint16_t amount_to_add = LSDLELIB::string_to_uint16(amount->content);

    Item* item;

    for(uint8_t i = 0; i < amount_to_add; ++i)
    {
        item = new Item;

        item->name = name->content;

        // Get item's attributes
        for(const MenuToolText& text_item : attributes->content)
        {
            item->attributes.push_back(text_item.content);
        }

        (*focused_character)->inventory.push_back(item);
    }

    exit_menu();
}

void AddInventoryItemMenu::exit_menu() 
{
    deactivate_menu();
    input_handler->block_key_until_released(SDLK_RETURN);
}

#include "LMath.h"
#include "LSDLE.h"

#include "ViewInventoryMenu.h"


// Constructors / Deconstructor

ViewInventoryMenu::ViewInventoryMenu(Character** _focused_character) : Menu("ViewInventory")
{
    focused_character = _focused_character;

    int screen_width = LSDLE::get_screen_width();
    int screen_height = LSDLE::get_screen_height();

    window->resize_window(0, 0, screen_width * .45, screen_height);

    inventory_window = new Window(screen_width * .48, 0, screen_width, screen_height);

    confirm_deletion_lsdc.content.push_back(ColorString("Yes", "Green"));
    confirm_deletion_lsdc.content.push_back(ColorString("No", "Red"));

    lsdc.content.push_back(ColorString("Add Item", "Green"));
    lsdc.content.push_back(ColorString("Edit Item", "Orange"));
    lsdc.content.push_back(ColorString("Delete Item", "Red"));
    lsdc.content.push_back(ColorString("<--", "Red"));
}


// Public

void ViewInventoryMenu::start() 
{
    lsdc.reset();
    inventory_cursor_pos = 0;

    confirm_deletion_lsdc.reset();

    // Start the cursor at the 1st position so the "No" option is default hovered
    confirm_deletion_lsdc.cursor_pos = 1;

    target_update_function = &ViewInventoryMenu::main_update_function;
}

void ViewInventoryMenu::update() 
{
    (this->*target_update_function)();
}


// Private

void ViewInventoryMenu::main_update_function()
{
    window->add_str("[...][...][ Simulation Menu / View Inventory ]\n\n");

    menu_tools->simulate_list_selection(lsdc);

    handle_inventory_page();

    if(!lsdc.item_has_been_selected) return;

    lsdc.item_has_been_selected = false;
    input_handler->block_key_until_released(SDLK_RETURN);

    const std::string& selected_item = lsdc.get_selected_item();

    if(selected_item == "Add Item") 
    {
        MenuHandler::activate_menu("AddInventoryItem");
        return;
    }

    else if(selected_item == "Edit Item")
    {
        return;
    }

    else if(selected_item == "Delete Item")
    {
        // There are no items in the inventory, do nothing
        if((*focused_character)->inventory.size() == 0) return;

        // Otherwise, switch to the confirm deletion update function to verify if the user is sure
        // they want to delete this item
        target_update_function = ViewInventoryMenu::confirm_deletion_update_function;
        return;
    }
        
    // else: selected_item == "<--"
    deactivate_menu();
}

void ViewInventoryMenu::confirm_deletion_update_function()
{
    window->add_str("\nAre you sure you want to delete the \"" + 
        (*focused_character)->inventory.at(inventory_cursor_pos)->name + "\" ?\n\n");

    menu_tools->simulate_list_selection(confirm_deletion_lsdc);

    if(!confirm_deletion_lsdc.item_has_been_selected) return;

    if(confirm_deletion_lsdc.get_selected_item() == "No") 
    {
        confirm_deletion_lsdc.reset();
        confirm_deletion_lsdc.cursor_pos = 1;
        target_update_function = &ViewInventoryMenu::main_update_function;
        return;
    }

    
    // Create an alias for the inventory
    std::vector<Item*>& inventory = (*focused_character)->inventory;
    
    // Delete the Item from memory
    delete inventory.at(inventory_cursor_pos);

    // Erase it from the inventory
    inventory.erase(
        inventory.begin() + inventory_cursor_pos);

    confirm_deletion_lsdc.reset();
    confirm_deletion_lsdc.cursor_pos = 1;
    target_update_function = &ViewInventoryMenu::main_update_function;

    // If the cursor position is at the end of the inventory, and is not the only item in it.
    // The reason there is no " - 1" deducted from the inventory size, is because the item has
    // already been erased, and hence the inventory is one smaller than where the cursor was 
    // originally pointing. If the cursor was at the end, it will now be equal to the exact
    // size of the inventory, not the index of the last element that is now gone. Similarily,
    // the check for if the item is the only one in inventory is compared to be greater than 0,
    // since if it was the only item in the inventory and that only item was just deleted, the 
    // size would be zero. Slightly confusing, but it saves having to make an extra variable for
    // the saving the index before decreaseing the cursor position and then deleting at the index
    if(inventory_cursor_pos == inventory.size() && inventory.size() > 0)
    {
        // Decrement the cursor, since the last item in the inventory is deleted, and the hovered
        // position is now out of bounds.
        --inventory_cursor_pos;
        return;
    }
}

void ViewInventoryMenu::handle_inventory_page()
{
    inventory_window->add_str(" -- Inventory --\n\n");

    if((*focused_character)->inventory.size() == 0) return;

    render_inventory();
    check_input_for_inventory_page();
}

void ViewInventoryMenu::render_inventory()
{
    const std::vector<Item*>& inventory = (*focused_character)->inventory;

    // Render items before the cursor's position
    for(uint16_t i = 0; i < inventory_cursor_pos; ++i)
    {
        inventory_window->add_str("   " + inventory.at(i)->name + "\n");

        // If there are attributes tied to this item, render an icon to portray that
        if(inventory.at(i)->attributes.size() > 0)
        {
            inventory_window->add_str("      [...]\n", "LightGray");
        }
    }

    // Render the item that is hovered by the cursor
    inventory_window->add_str(" > ", "Blue");
    inventory_window->add_str(inventory.at(inventory_cursor_pos)->name + "\n");

    // If there are attributes tied to this item, render an icon to portray that
    if(inventory.at(inventory_cursor_pos)->attributes.size() > 0)
    {
        // inventory_window->add_str("      [...]\n", "LightGray");
        for(const std::string& attrib : inventory.at(inventory_cursor_pos)->attributes)
        {
            inventory_window->add_str("      " + attrib + '\n', "LightGray");
        }
    }

    // Render items after the cursor's position
    for(uint16_t i = inventory_cursor_pos + 1; i < inventory.size(); ++i)
    {
        inventory_window->add_str("   " + inventory.at(i)->name + '\n');

        // If there are attributes tied to this item, render an icon to portray that
        if(inventory.at(i)->attributes.size() > 0)
        {
            inventory_window->add_str("      [...]\n", "LightGray");
        }
    }
}

void ViewInventoryMenu::check_input_for_inventory_page()
{
    const std::vector<Item*>& inventory = (*focused_character)->inventory;

    if(input_handler->is_key_pressed_and_available(SDLK_DOWN))
    {
        if(input_handler->is_key_pressed(SDLK_LSHIFT))
        {
            inventory_cursor_pos = inventory.size() - 1;
            input_handler->set_delay(SDLK_DOWN);
            return;
        }

        inventory_cursor_pos = LSDLELIB::round_num_to_maximum(++inventory_cursor_pos, 
            inventory.size() - 1);

        input_handler->set_delay(SDLK_DOWN);
        return;
    }

    else if(input_handler->is_key_pressed_and_available(SDLK_UP))
    {
        if(input_handler->is_key_pressed(SDLK_LSHIFT))
        {
            inventory_cursor_pos = 0;
            input_handler->set_delay(SDLK_UP);
            return;
        }

        inventory_cursor_pos > 0 ? --inventory_cursor_pos : 0;
        input_handler->set_delay(SDLK_UP);
        return;
    }
}

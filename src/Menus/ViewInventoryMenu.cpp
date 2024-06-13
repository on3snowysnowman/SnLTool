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

    lsdc.content.push_back(ColorString("Add Item", "Green"));
    lsdc.content.push_back(ColorString("View Item", "White"));
    lsdc.content.push_back(ColorString("Edit Item", "Orange"));
    lsdc.content.push_back(ColorString("Delete Item", "Red"));
    lsdc.content.push_back(ColorString("<--", "Red"));
}


// Public

void ViewInventoryMenu::start() 
{
    lsdc.reset();
    inventory_cursor_pos = 0;
}

void ViewInventoryMenu::update() 
{
    window->add_str("[...][...][ Simulation Menu / View Inventory ]\n\n");

    menu_tools->simulate_list_selection(lsdc);

    handle_inventory_page();

    if(!lsdc.item_has_been_selected) return;

    lsdc.item_has_been_selected = false;

    const std::string& selected_item = lsdc.get_selected_item();

    if(selected_item == "Add Item") 
    {
        MenuHandler::activate_menu("AddInventoryItem");
        return;
    }

    else if(selected_item == "View Item")
    {
        return;
    }

    else if(selected_item == "Edit Item")
    {
        return;
    }

    else if(selected_item == "Delete Item")
    {
        return;
    }
        
    // else: selected_item == "<--"
    deactivate_menu();
    input_handler->block_key_until_released(SDLK_RETURN);
}


// Private

void ViewInventoryMenu::handle_inventory_page()
{
    inventory_window->add_str(" -- Inventory --\n\n");

    if((*focused_character)->inventory.size() == 0) return;

    render_inventory();
    check_input_for_inventory_page();
}

void ViewInventoryMenu::render_inventory()
{
    const std::vector<Item*>* inventory = &(*focused_character)->inventory;

    // Render items before the cursor's position
    for(uint16_t i = 0; i < inventory_cursor_pos; ++i)
    {
        inventory_window->add_str(inventory->at(i)->name + "\n");

        // If there are attributes tied to this item, render an icon to portray that
        if(inventory->at(i)->attributes.size() > 0)
        {
            inventory_window->add_str("   [...]\n", "LightGray");
        }
    }

    // Render the item that is hovered by the cursor
    inventory_window->add_str(" > ", "Blue");
    inventory_window->add_str(inventory->at(inventory_cursor_pos)->name + "\n");

    // If there are attributes tied to this item, render an icon to portray that
    if(inventory->at(inventory_cursor_pos)->attributes.size() > 0)
    {
        inventory_window->add_str("   [...]\n", "LightGray");
    }

    // Render items after the cursor's position
    for(uint16_t i = 0; i < inventory->size(); ++i)
    {
        inventory_window->add_str(inventory->at(i)->name + "\n");

        // If there are attributes tied to this item, render an icon to portray that
        if(inventory->at(i)->attributes.size() > 0)
        {
            inventory_window->add_str("   [...]\n", "LightGray");
        }
    }
}

void ViewInventoryMenu::check_input_for_inventory_page()
{
    const std::vector<Item*>* inventory = &(*focused_character)->inventory;

    if(input_handler->is_key_pressed_and_available(SDLK_DOWN))
    {
        if(input_handler->is_key_pressed(SDLK_LSHIFT))
        {
            inventory_cursor_pos = inventory->size() - 1;
            input_handler->set_delay(SDLK_DOWN);
            return;
        }

        LSDLELIB::round_num_to_maximum(++inventory_cursor_pos, 
            inventory->size() - 1);
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

#include "Menu.h"
#include "LInts.h"

#include "Character.h"

class ViewInventoryMenu : public Menu
{

public:

    ViewInventoryMenu(Character** focused_character);

    void start() final;
    void update() final;

private:

    // Members

    using function_ptr = void (ViewInventoryMenu::*)();

    function_ptr target_update_function;

    uint16_t inventory_cursor_pos {};

    Character** focused_character {};

    ListSelectionDataContainer confirm_deletion_lsdc;
    ListSelectionDataContainer lsdc;

    Window* inventory_window {};

    // Methods

    void main_update_function();
    void confirm_deletion_update_function();

    void handle_inventory_page();
    void render_inventory();
    void check_input_for_inventory_page();
};

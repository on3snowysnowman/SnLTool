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

    uint16_t inventory_cursor_pos {};

    Character** focused_character {};

    ListSelectionDataContainer lsdc;

    Window* inventory_window {};

    // Functions

    void handle_inventory_page();
    void render_inventory();
    void check_input_for_inventory_page();
};

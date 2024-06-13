#include "Menu.h"
#include "MenuToolVariable.h"
#include "MenuToolTextList.h"
#include "MenuToolButton.h"

#include "Character.h"

class AddInventoryItemMenu : public Menu
{

public:

    AddInventoryItemMenu(Character** focused_character);

    void start() final;
    void update() final;

private:

    // Members

    Character** focused_character;

    MenuSimulationDataContainer msdc;

    MenuToolVariable* name;
    MenuToolTextList* attributes;
    MenuToolVariable* amount;
    MenuToolButton<AddInventoryItemMenu>* add_button;
    MenuToolButton<AddInventoryItemMenu>* cancel_button;

    // Functions

    void handle_add_item();
    void exit_menu();
};

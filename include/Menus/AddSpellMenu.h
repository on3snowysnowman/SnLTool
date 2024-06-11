#pragma once

#include "Menu.h"

#include "MenuToolVariable.h"
#include "MenuToolButton.h"


class AddSpellMenu : public Menu
{

public:

    AddSpellMenu();

    void start();
    void update();


private:

    const std::string SPELLS_PATH = "data/Spells.json";

    MenuSimulationDataContainer msdc;

    MenuToolVariable* name {};
    MenuToolVariable* description {};
    MenuToolVariable* arcanary_level {};
    MenuToolVariable* mana_cost {};
    MenuToolVariable* casting_time {};
    MenuToolVariable* range {};
    MenuToolVariable* duration {};
    MenuToolVariable* damage {};
    MenuToolVariable* per_level_increase {};
    MenuToolVariable* upgrades {};

    MenuToolButton<AddSpellMenu>* add_button {};
    MenuToolButton<AddSpellMenu>* cancel_button {};

    void handle_add_spell();
    void exit_menu();
};


#pragma once

#include "Menu.h"
#include "MenuToolVariable.h"
#include "MenuToolButton.h"


class AddPotionMenu : public Menu
{

public:

    AddPotionMenu();

    void start() final;
    void update() final;

private:

    const std::string POTIONS_PATH = "data/potions.json";

    MenuSimulationDataContainer msdc;

    MenuToolVariable* name {};
    MenuToolVariable* description {};
    MenuToolVariable* ingredients {};
    
    MenuToolButton<AddPotionMenu>* add_button {};
    MenuToolButton<AddPotionMenu>* cancel_button {};

    void handle_add_potion();
    void exit_menu();
};

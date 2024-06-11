#pragma once

#include <vector>

#include "LInts.h"
#include "SimulationDataContainers.h"
#include "Menu.h"
#include "MenuToolVariable.h"
#include "MenuToolButton.h"

#include "Character.h"


class CreateCharacterMenu : public Menu
{

public:

    CreateCharacterMenu(std::vector<Character*>* all_characters);

    void start() final;
    void update() final;

private:

    std::vector<Character*>* all_characters;

    MenuSimulationDataContainer msdc;

    MenuToolVariable* name {};
    MenuToolVariable* race {};
    MenuToolVariable* max_hitpoints {};
    MenuToolVariable* max_mana {};

    MenuToolButton<CreateCharacterMenu>* cancel_button {};
    MenuToolButton<CreateCharacterMenu>* create_button {};

    void create_character();

    void exit_menu();

};

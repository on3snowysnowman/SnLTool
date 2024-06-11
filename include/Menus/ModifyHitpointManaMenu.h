#pragma once

#include "Menu.h"
#include "MenuToolChoice.h"
#include "MenuToolVariable.h"
#include "MenuToolButton.h"

#include "Character.h"


class ModifyHitpointManaMenu : public Menu
{

public:

    ModifyHitpointManaMenu(Character** focused_character);

    void start() final;
    void update() final;

private:

    Character** focused_character {};

    MenuSimulationDataContainer msdc;

    MenuToolChoice* modification_choice {};
    MenuToolVariable* modification_amount {};
    MenuToolButton<ModifyHitpointManaMenu>* increase_button {};
    MenuToolButton<ModifyHitpointManaMenu>* decrease_button {};
    MenuToolButton<ModifyHitpointManaMenu>* back_button {};
    
    void render_character_stats();
    void handle_increase();
    void handle_decrease();
    void exit_menu();
};

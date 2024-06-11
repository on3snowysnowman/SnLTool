#pragma once

#include "Menu.h"
#include "LInts.h"

#include "Character.h"


class SimulationMenu : public Menu
{

public:

    SimulationMenu(Character** focused_character);


    void start() final;
    void update() final;

private:

    Character** focused_character;

    ListSelectionDataContainer lsdc;

    void render_character_stats();
};

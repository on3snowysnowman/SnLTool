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

    // Members

    using function_ptr = void (SimulationMenu::*)();

    function_ptr target_stat_render_function {};

    Character** focused_character;

    ListSelectionDataContainer lsdc;

    Window* first_stats_window;
    Window* second_stats_window;

    MenuTools* first_stats_menu_tools;
    MenuTools* second_stats_menu_tools;

    // Functions

    void render_first_page_stats();
    void render_second_page_stats();
    // void render_inventory_page();
};

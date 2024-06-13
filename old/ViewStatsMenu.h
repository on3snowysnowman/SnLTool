#pragma once

#include "Menu.h"

#include "Character.h"

class ViewStatsMenu : public Menu
{

public:

    ViewStatsMenu(Character** focused_character);

    void start() final;
    void update() final;

private:

    using function_ptr = void (ViewStatsMenu::*)();

    function_ptr target_stat_render_function {};

    Character** focused_character {};

    ListSelectionDataContainer lsdc;

    Window* first_stats_window;
    Window* second_stats_window;

    MenuTools* first_stats_menu_tools;
    MenuTools* second_stats_menu_tools;

    void render_first_page_stats();
    void render_second_page_stats();
};

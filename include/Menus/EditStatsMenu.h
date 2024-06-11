#pragma once

#include "Menu.h"
#include "MenuToolVariable.h"
#include "MenuToolButton.h"
#include "MenuToolTextList.h"

#include "Character.h"


class EditStatsMenu : public Menu
{

public:

    EditStatsMenu(Character** focused_character);

    void start() final;
    void update() final;

private:

    using function_ptr = void (EditStatsMenu::*)();

    function_ptr target_update_function {};

    uint8_t stats_last_position {};
    uint8_t skills_last_position {};

    Character** focused_character {};

    MenuSimulationDataContainer msdc;

    MenuToolVariable* name {};
    MenuToolVariable* max_hitpoints {};
    MenuToolVariable* max_mana {};
    MenuToolVariable* race {};
    MenuToolVariable* character_class {};
    MenuToolVariable* height {};
    MenuToolVariable* weight {};
    MenuToolVariable* speed {};
    MenuToolVariable* description {};
    MenuToolButton<EditStatsMenu>* save_button {};
    MenuToolButton<EditStatsMenu>* cancel_button {};

    MenuToolVariable* alchemy_skill {};
    MenuToolVariable* anim_hand_skill {};
    MenuToolVariable* appraising_skill {};
    MenuToolVariable* arcanary_skill {};
    MenuToolVariable* athletics_skill {};
    MenuToolVariable* cooking_skill {};
    MenuToolVariable* intelligence_skill {};
    MenuToolVariable* medicine_skill {};
    MenuToolVariable* perception_skill {};
    MenuToolVariable* speech_skill {};
    MenuToolVariable* stealth_skill {};
    MenuToolVariable* strength_skill {};
    MenuToolVariable* survival_skill {};
    MenuToolVariable* sl_of_hand_skill {};
    MenuToolButton<EditStatsMenu>* randomize_skills_button {};

    MenuToolTextList* attributes {};

    MenuToolTextList* effects {};

    void handle_stats_page();

    void handle_skills_page();

    void handle_attributes_page();

    void handle_effects_page();

    void set_menu_tool_item_data();

    void handle_randomize_skills();

    void handle_save();

    void exit_menu();
};

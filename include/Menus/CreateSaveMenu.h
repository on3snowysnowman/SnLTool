#pragma once

#include "Menu.h"
#include "MenuToolVariable.h"
#include "MenuToolButton.h"

#include "CreateSaveMenu.h"
#include "SaveHandler.h"


class CreateSaveMenu : public Menu
{

public:

    CreateSaveMenu(SaveHandler* save_handler);

    void start() final;
    void update() final;

private:

    using function_ptr = void (CreateSaveMenu::*)();

    function_ptr target_function {};

    MenuSimulationDataContainer msdc;

    MenuToolVariable* save_name {};

    MenuToolButton<CreateSaveMenu>* cancel_button {};
    MenuToolButton<CreateSaveMenu>* create_button {};

    SaveHandler* save_handler {};

    void main_update_function();
    void creation_failed_update_function();

    void handle_save_creation();
    void exit_menu();
};

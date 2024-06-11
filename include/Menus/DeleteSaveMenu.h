#pragma once

#include "Menu.h"

#include "DeleteSaveMenu.h"
#include "SaveHandler.h"

class DeleteSaveMenu : public Menu
{

public:

    DeleteSaveMenu(SaveHandler* save_handler);

    void start() override;
    void update() override;

private:

    using function_ptr = void (DeleteSaveMenu::*)();

    function_ptr target_function;

    ListSelectionDataContainer lsdc;
    ListSelectionDataContainer confirm_deletion_lsdc;

    SaveHandler* save_handler;

    void main_update_function();
    void confirm_save_deletion_update_function();
};

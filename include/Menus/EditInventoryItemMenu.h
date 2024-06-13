#pragma once

#include "Menu.h"
#include "MenuToolVariable.h"


class EditInventoryItemMenu : public Menu
{

public:

    EditInventoryItemMenu();

    void start() final;
    void update() final;

private:

    // Members

    // Methods
};

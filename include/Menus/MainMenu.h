#pragma once

#include "Menu.h"


class MainMenu : public Menu
{

public:

    MainMenu();

    void start() override;
    void update() override;

private:

    ListSelectionDataContainer lsdc;

};

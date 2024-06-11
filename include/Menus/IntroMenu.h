#pragma once

#include "Menu.h"

class IntroMenu : public Menu
{

public:

    IntroMenu(Sprite* logo);

    void start() final;
    void update() final;

private:

    ListSelectionDataContainer lsdc;

    Sprite* logo;
};

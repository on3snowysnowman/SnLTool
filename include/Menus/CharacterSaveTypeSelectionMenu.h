#pragma once

#include <string>

#include "Menu.h"
#include "SimulationDataContainers.h"
#include "LInts.h"

class CharacterSaveTypeSelectionMenu : public Menu
{

public:

    CharacterSaveTypeSelectionMenu();

    void start() final;
    void update() final;

private:

    ListSelectionDataContainer lsdc;

};

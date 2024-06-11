#pragma once

#include "Menu.h"

#include "SaveHandler.h"


class SaveLoadMenu : public Menu
{

public:

    SaveLoadMenu(SaveHandler* save_handler,
        std::vector<Character*>* all_characters);

    void start() override;
    void update() override;

private:

    ListSelectionDataContainer lsdc;

    std::vector<Character*>* all_characters;

    SaveHandler* save_handler;

    void fetch_saves_on_disk();
};

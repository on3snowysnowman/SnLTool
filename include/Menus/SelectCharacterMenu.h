#pragma once

#include <vector>

#include "Menu.h"
#include "LInts.h"

#include "Character.h"

class SelectCharacterMenu : public Menu
{

public:

    SelectCharacterMenu(Character** focused_character, 
        std::vector<Character*>* all_characters);

    void start() final;
    void update() final;

private:

    Character** focused_character {};

    std::vector<Character*>* all_characters {};

    ListSelectionDataContainer lsdc;
};
#pragma once

#include <string>
#include <vector>
#include <array>

#include "LInts.h"

#include "Item.h" 
#include "Spell.h"

struct Character
{
    uint16 hitpoints {};
    uint16 max_hitpoints {};

    uint16 mana {};
    uint16 max_mana {};

    std::string name;
    std::string race;
    std::string character_class;
    std::string height;
    std::string weight;
    std::string speed;
    std::string description;

    std::array<uint8_t, 14> skills;

    std::vector<std::string> effects;

    std::vector<std::string> attributes;

    std::vector<Spell*> spells;

    std::vector<Item*> inventory;


};

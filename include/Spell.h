#pragma once

#include <string>

#include "LInts.h"

struct Spell
{
    std::string name;
    std::string description;
    std::string casting_time;
    std::string range;
    std::string duration;
    std::string damage;
    std::string per_level_increase;
    std::string upgrades;

    uint8_t arcanary_level;
    uint16_t mana_cost;

};

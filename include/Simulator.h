#pragma once

#include <vector>

#include "LSDLE.h"

#include "SaveHandler.h"

class Simulator : public LSDLE
{

public:

    Simulator();

    void start_simulation();

    void update() final;
    void render() final;

private:

    // Members

    std::vector<Character*> all_characters;

    Character* focused_character {}; 

    SaveHandler* save_handler {};

    // Methods

    void create_menus();

    void save_characters() const;

    void stop_engine();    

};
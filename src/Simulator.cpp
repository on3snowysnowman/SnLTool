#include "Simulator.h"
#include "EventSystem.h"
#include "MenuHandler.h"
#include "AllMenus.h"

// Constructors / Deconstructor 

Simulator::Simulator() : LSDLE("C:/Users/Joel/LSDLE")
{
    CallbackManager::subscribe<Simulator>("quit", this, stop_engine);
    CallbackManager::subscribe<Simulator>("save_characters", this, 
        save_characters);

    save_handler = new SaveHandler();
    
    int screen_width = LSDLE::get_screen_width();
    int screen_height = LSDLE::get_screen_height();

    create_menus();    
}


// Public

void Simulator::start_simulation() { start(); }

void Simulator::update() {}

void Simulator::render() {}


// Private

void Simulator::create_menus() 
{
    MainMenu* main_m = new MainMenu();
    CreateCharacterMenu* create_c_m = new CreateCharacterMenu(&all_characters);
    SelectCharacterMenu* select_c_m = new SelectCharacterMenu(
        &focused_character, &all_characters);
    SimulationMenu* sim_m = new SimulationMenu(&focused_character);
    ModifyHitpointManaMenu* modify_hit_man_m = new 
        ModifyHitpointManaMenu(&focused_character);

    Sprite* logo = SpriteHandler::create_sprite("assets/SnLLogo.png", 0, 0, 
        200, 140, 1000, 700, false);

    IntroMenu* intro_m = new IntroMenu(logo);
    CharacterSaveTypeSelectionMenu* char_save_type_sel_m = 
        new CharacterSaveTypeSelectionMenu();
    SaveLoadMenu* save_load_m = new SaveLoadMenu(save_handler, 
        &all_characters);
    CreateSaveMenu* create_save_m = new CreateSaveMenu(save_handler);
    DeleteSaveMenu* del_save_m = new DeleteSaveMenu(save_handler);
    AddSpellMenu* add_spell_m = new AddSpellMenu();
    AddPotionMenu* add_pot_m = new AddPotionMenu();
    EditStatsMenu* edit_stats_m = new EditStatsMenu(&focused_character);
    ViewInventoryMenu* view_inv_m = new ViewInventoryMenu(&focused_character);
    AddInventoryItemMenu* add_inv_item_m = new AddInventoryItemMenu(&focused_character);

    MenuHandler::activate_menu(intro_m);
}

void Simulator::save_characters() const
{
    save_handler->save_characters_to_disk(all_characters);
}

void Simulator::stop_engine() 
{   
    quit();
}

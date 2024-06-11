#include "LStringManip.h"
#include "LMath.h"
#include "LRandom.h"
#include "LInts.h"

#include "EditStatsMenu.h"


// Constructors / Deconstructor 

EditStatsMenu::EditStatsMenu(Character** _focused_character) : Menu("EditStats")
{
    focused_character = _focused_character;

    name = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", "Name");
    max_hitpoints = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Max Hitpoints");
    max_mana = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Max Mana");
    race = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", "Race");
    character_class = new MenuToolVariable(window, MenuToolItem::STRING, 
        "Blue", "Class");
    height = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", 
        "Height");
    weight = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", 
        "Weight");
    speed = new MenuToolVariable(window, MenuToolItem::STRING, "Blue", 
        "Speed");
    description = new MenuToolVariable(window, MenuToolItem::STRING, "Blue",
        "Description");
    save_button = new MenuToolButton<EditStatsMenu>(this, handle_save, window, 
        "Save", "Blue", "Green");
    cancel_button = new MenuToolButton<EditStatsMenu>(this, exit_menu, window,
        "Cancel", "Blue", "Red");


    alchemy_skill = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Alchemy");
    anim_hand_skill = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Animal Handling");
    appraising_skill = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Appraising");
    arcanary_skill = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Arcanary");
    athletics_skill = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Athetlics");
    cooking_skill = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Cooking");
    intelligence_skill = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Intelligence");
    medicine_skill = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Medicine");
    perception_skill = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Perception");
    speech_skill = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Speech");
    stealth_skill = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Stealth");
    strength_skill = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Strength");
    survival_skill = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Survival");
    sl_of_hand_skill = new MenuToolVariable(window, MenuToolItem::INT, "Blue", 
        "Slight of Hand");
    randomize_skills_button = new MenuToolButton<EditStatsMenu>(this, 
        handle_randomize_skills, window, "Randomize Skills", "Blue", "Purple");

    attributes = new MenuToolTextList(window, "Blue", "Attributes");

    effects = new MenuToolTextList(window, "Blue", "Effects");
}


// Public

void EditStatsMenu::start() 
{
    msdc.reset();
    set_menu_tool_item_data();

    msdc.content.clear();
    msdc.fill_content({name, max_hitpoints, max_mana, race, character_class,
        height, weight, speed, description, save_button, cancel_button});

    target_update_function = &handle_stats_page;
}

void EditStatsMenu::update() 
{
    window->add_str("[...][...][ Simulation Menu / View Stats / Edit Stats ]"
        "\n\n");

    (this->*target_update_function)();
}


// Private

void EditStatsMenu::handle_stats_page() 
{
    window->add_str("[ Stats ][...][...][...]\n\n");

    menu_tools->simulate_menu(msdc);

    if(msdc.selected_pos > -1) return;

    if(input_handler->is_key_pressed_and_available(SDLK_RIGHT))
    {
        stats_last_position = msdc.cursor_pos;
        msdc.reset();
        msdc.cursor_pos = skills_last_position;

        input_handler->block_key_until_released(SDLK_RIGHT);
        target_update_function = &handle_skills_page;

        msdc.content.clear();
        msdc.fill_content({alchemy_skill, anim_hand_skill, appraising_skill, 
            arcanary_skill, athletics_skill, cooking_skill, intelligence_skill,
            medicine_skill, perception_skill, speech_skill, stealth_skill, 
            strength_skill, survival_skill, sl_of_hand_skill, 
            randomize_skills_button, save_button, cancel_button});
    }
}

void EditStatsMenu::handle_skills_page() 
{
    window->add_str("[...][ Skills ][...][...]\n\n");

    menu_tools->simulate_menu(msdc);

    if(msdc.selected_pos > -1) return;

    if(input_handler->is_key_pressed_and_available(SDLK_RIGHT))
    {
        skills_last_position = msdc.cursor_pos;
        msdc.reset();

        input_handler->block_key_until_released(SDLK_RIGHT);
        target_update_function = &handle_attributes_page;

        msdc.content.clear();
        msdc.fill_content({attributes, save_button, cancel_button});
    }

    else if(input_handler->is_key_pressed_and_available(SDLK_LEFT))
    {
        skills_last_position = msdc.cursor_pos;
        msdc.reset();
        msdc.cursor_pos = stats_last_position;

        input_handler->block_key_until_released(SDLK_LEFT);
        target_update_function = &handle_stats_page;

        msdc.content.clear();
        msdc.fill_content({name, max_hitpoints, max_mana, race, character_class,
            height, weight, speed, description, save_button, cancel_button});
    }
}

void EditStatsMenu::handle_attributes_page() 
{
    window->add_str("[...][...][ Attributes ][...]\n\n");


    menu_tools->simulate_menu(msdc);

    if(msdc.selected_pos > -1) return;

    if(input_handler->is_key_pressed_and_available(SDLK_RIGHT))
    {
        msdc.reset();

        input_handler->block_key_until_released(SDLK_RIGHT);
        target_update_function = &handle_effects_page;

        msdc.content.clear();
        msdc.fill_content({effects, save_button, cancel_button});
    }

    else if(input_handler->is_key_pressed_and_available(SDLK_LEFT))
    {
        msdc.reset();
        msdc.cursor_pos = skills_last_position;

        input_handler->block_key_until_released(SDLK_LEFT);
        target_update_function = &handle_skills_page;

        msdc.content.clear();
        msdc.fill_content({alchemy_skill, anim_hand_skill, appraising_skill, 
            arcanary_skill, athletics_skill, cooking_skill, intelligence_skill,
            medicine_skill, perception_skill, speech_skill, stealth_skill, 
            strength_skill, survival_skill, sl_of_hand_skill, 
            randomize_skills_button, save_button, cancel_button});
    }
}

void EditStatsMenu::handle_effects_page() 
{
    window->add_str("[...][...][...][ Effects ]\n\n");

    menu_tools->simulate_menu(msdc);

    if(msdc.selected_pos > -1) return;

    if(input_handler->is_key_pressed_and_available(SDLK_LEFT))
    {
        msdc.reset();

        input_handler->block_key_until_released(SDLK_LEFT);
        target_update_function = &handle_attributes_page;

        msdc.content.clear();
        msdc.fill_content({attributes, save_button, cancel_button});
    }
}

void EditStatsMenu::set_menu_tool_item_data() 
{
    name->content = (*focused_character)->name;
    max_hitpoints->content = std::to_string((*focused_character)->max_hitpoints);
    max_mana->content = std::to_string((*focused_character)->max_mana);
    race->content = (*focused_character)->race;
    character_class->content = (*focused_character)->character_class;
    height->content = (*focused_character)->height;
    weight->content = (*focused_character)->weight;
    speed->content = (*focused_character)->speed;
    description->content = (*focused_character)->description;

    alchemy_skill->content = std::to_string(
        (*focused_character)->skills.at(0));
    anim_hand_skill->content = std::to_string(
        (*focused_character)->skills.at(1));
    appraising_skill->content = std::to_string(
        (*focused_character)->skills.at(2));
    arcanary_skill->content = std::to_string(
        (*focused_character)->skills.at(3));
    athletics_skill->content = std::to_string(
        (*focused_character)->skills.at(4));
    cooking_skill->content = std::to_string(
        (*focused_character)->skills.at(5));
    intelligence_skill->content = std::to_string(
        (*focused_character)->skills.at(6));
    medicine_skill->content = std::to_string(
        (*focused_character)->skills.at(7));
    perception_skill->content = std::to_string(
        (*focused_character)->skills.at(8));
    speech_skill->content = std::to_string(
        (*focused_character)->skills.at(9));
    stealth_skill->content = std::to_string(
        (*focused_character)->skills.at(10));
    strength_skill->content = std::to_string(
        (*focused_character)->skills.at(11));
    survival_skill->content = std::to_string(
        (*focused_character)->skills.at(12));
    sl_of_hand_skill->content = std::to_string(
        (*focused_character)->skills.at(13));
    
    attributes->content.clear();

    for(const std::string& _str : (*focused_character)->attributes)
    {
        attributes->content.push_back(MenuToolText(window, "Blue", _str));
    }

    effects->content.clear();

    for(const std::string& _str : (*focused_character)->effects)
    {
        effects->content.push_back(MenuToolText(window, "Blue", _str));
    }
}

void EditStatsMenu::handle_randomize_skills()
{
    alchemy_skill->content = 
        std::to_string(LRandomGenerator::get_random_num(1, 20));
    anim_hand_skill->content = 
        std::to_string(LRandomGenerator::get_random_num(1, 20));
    appraising_skill->content = 
        std::to_string(LRandomGenerator::get_random_num(1, 20));
    arcanary_skill->content = 
        std::to_string(LRandomGenerator::get_random_num(1, 20));
    athletics_skill->content = 
        std::to_string(LRandomGenerator::get_random_num(1, 20));
    cooking_skill->content = 
        std::to_string(LRandomGenerator::get_random_num(1, 20));
    intelligence_skill->content = 
        std::to_string(LRandomGenerator::get_random_num(1, 20));
    medicine_skill->content = 
        std::to_string(LRandomGenerator::get_random_num(1, 20));
    perception_skill->content = 
        std::to_string(LRandomGenerator::get_random_num(1, 20));
    speech_skill->content = 
        std::to_string(LRandomGenerator::get_random_num(1, 20));
    stealth_skill->content = 
        std::to_string(LRandomGenerator::get_random_num(1, 20));
    strength_skill->content = 
        std::to_string(LRandomGenerator::get_random_num(1, 20));
    survival_skill->content = 
        std::to_string(LRandomGenerator::get_random_num(1, 20));;
    sl_of_hand_skill->content = 
        std::to_string(LRandomGenerator::get_random_num(1, 20));;

    input_handler->block_key_until_released(SDLK_RETURN);
}

void EditStatsMenu::handle_save()
{
    (*focused_character)->name = name->content;
    
    (*focused_character)->max_hitpoints = 
        LSDLELIB::string_to_int32(max_hitpoints->content);
    (*focused_character)->hitpoints = LSDLELIB::round_num_to_maximum(
        (*focused_character)->hitpoints, (*focused_character)->max_hitpoints);

    (*focused_character)->max_mana = 
        LSDLELIB::string_to_int32(max_mana->content);
    (*focused_character)->mana = LSDLELIB::round_num_to_maximum(
        (*focused_character)->mana, (*focused_character)->max_mana);

    (*focused_character)->race = race->content;
    (*focused_character)->character_class = character_class->content;
    (*focused_character)->height = height->content;
    (*focused_character)->weight = weight->content;
    (*focused_character)->speed = speed->content;
    (*focused_character)->description = description->content;

    (*focused_character)->skills.at(0) = 
        LSDLELIB::string_to_uint8(alchemy_skill->content);
    (*focused_character)->skills.at(1) = 
        LSDLELIB::string_to_uint8(anim_hand_skill->content);
    (*focused_character)->skills.at(2) = 
        LSDLELIB::string_to_uint8(appraising_skill->content);
    (*focused_character)->skills.at(3) = 
        LSDLELIB::string_to_uint8(arcanary_skill->content);
    (*focused_character)->skills.at(4) = 
        LSDLELIB::string_to_uint8(athletics_skill->content);
    (*focused_character)->skills.at(5) = 
        LSDLELIB::string_to_uint8(cooking_skill->content);
    (*focused_character)->skills.at(6) = 
        LSDLELIB::string_to_uint8(intelligence_skill->content);
    (*focused_character)->skills.at(7) = 
        LSDLELIB::string_to_uint8(medicine_skill->content);
    (*focused_character)->skills.at(8) = 
        LSDLELIB::string_to_uint8(perception_skill->content);
    (*focused_character)->skills.at(9) = 
        LSDLELIB::string_to_uint8(speech_skill->content);
    (*focused_character)->skills.at(10) = 
        LSDLELIB::string_to_uint8(stealth_skill->content);
    (*focused_character)->skills.at(11) = 
        LSDLELIB::string_to_uint8(strength_skill->content);
    (*focused_character)->skills.at(12) = 
        LSDLELIB::string_to_uint8(survival_skill->content);
    (*focused_character)->skills.at(13) = 
        LSDLELIB::string_to_uint8(sl_of_hand_skill->content);

    (*focused_character)->attributes.clear();

    for(const MenuToolText& text : attributes->content)
    {
        (*focused_character)->attributes.push_back(text.content);
    }

    (*focused_character)->effects.clear();

    for(const MenuToolText& text : effects->content)
    {
        (*focused_character)->effects.push_back(text.content);
    }

    exit_menu();
}

void EditStatsMenu::exit_menu()
{
    deactivate_menu();
    input_handler->block_key_until_released(SDLK_RETURN);
}

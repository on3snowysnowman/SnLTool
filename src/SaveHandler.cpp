#include "JSonLoader.h"
#include "FileSystemHandler.h"
#include "LStringManip.h"

#include "SaveHandler.h"


// Static Members

const std::string SaveHandler::SAVES_DIRECTORY 
    = "C:/users/Joel/documents/SnLTool_Saves";


// Constructors / Deconstructor

SaveHandler::SaveHandler()
{
    fetch_saves_from_disk();
}


// Public

void SaveHandler::save_characters_to_disk(
    const std::vector<Character*>& characters)
{
    Json full_save;

    // Iterate through each character
    for(Character* c : characters)
    {
        // Create a json of this character, and add it to the full save
        full_save.push_back(create_json_from_character(c));
    }

    // Dump the full save to the 
    JsonLoader::dump(full_save, active_save_path.c_str());
}

void SaveHandler::delete_save_from_disk(const std::string& save_path)
{
    FileSystemHandler::delete_file(save_path);

    // Refetch the saves now that they've changed
    fetch_saves_from_disk();
}

void SaveHandler::unregister_active_save() { active_save_path.clear(); }

bool SaveHandler::create_new_save_file_on_disk(std::string file_name)
{
    std::string temp_path = SAVES_DIRECTORY + "\\" + file_name + ".json";

    // Iterate through each of the already existent save paths
    for(const std::string& path : save_paths)
    {
        // This new path attempting to be created already exists.
        if(path == temp_path)
        {
            return false;
        }
    }

    // Set the active save path to the new file's directory
    active_save_path = temp_path;

    // Create an empty Json object save
    Json new_save = Json::object();

    // Create a new file, and dump the empty Json there. The purpose of 
    // creating a Json object to dump there, is it will ensure the file
    // is not empty or "null", as dumping an empty Json file there will 
    // simply put "null" into the file.
    JsonLoader::dump(new_save, active_save_path.c_str());

    // Refetch the saves now that there is a new save
    fetch_saves_from_disk();

    return true;
}

std::vector<Character*> SaveHandler::load_characters_from_save(
    std::string save_path)
{
    active_save_path = save_path;

    std::vector<Character*> characters;

    // Get the full save json from the save path
    Json save_json = JsonLoader::get(save_path.c_str());

    // Iterate through each character json 
    for(Json character_json : save_json)
    {
        // Add the created character to the list of characters
        characters.push_back(create_character_from_json(character_json));
    }

    return characters;
}

const std::vector<std::string>& SaveHandler::get_saves()
    const 
{ return save_paths; }


// Private

void SaveHandler::fetch_saves_from_disk()
{
    // Directory containing saves does not exist
    if(!FileSystemHandler::does_directory_exist(SAVES_DIRECTORY.c_str()))
    {
        // Create the directory
        FileSystemHandler::make_directory(SAVES_DIRECTORY);

        // Since the directory was just created, it is known there are no
        // possible saves yet, so return here to skip the loading phase

        return;
    }

    save_paths.clear();

    save_paths = FileSystemHandler::get_files_at_directory(SAVES_DIRECTORY);
}

Character* SaveHandler::create_character_from_json(Json character_json)
{
    Character* c = new Character;

    c->name = character_json["name"];
    c->race = character_json["race"];
    c->character_class = character_json["character_class"];
    c->height = character_json["height"];
    c->weight = character_json["weight"];
    c->speed = character_json["speed"];
    c->description = character_json["description"];
    c->hitpoints = character_json["hitpoints"];
    c->max_hitpoints = character_json["max_hitpoints"];
    c->mana = character_json["mana"];
    c->max_mana = character_json["max_mana"];

    // Load Skills
    Json temp = character_json["skills"];

    for(uint8_t i = 0; i < 14; ++i)
    {
        c->skills.at(i) = temp.at(i);
    }

    // Load Attributes
    temp = character_json["attributes"];

    for(const std::string& _str : temp)
    {
        c->attributes.push_back(_str);
    }

    // Load Effects
    temp = character_json["effects"];

    for(const std::string& _str : temp)
    {
        c->effects.push_back(_str);
    }

    // Load Inventory
    temp = character_json["inventory"];

    // Transfer Json for the Item
    Item* item;

    // Transfer Json for the attributes of each item
    Json item_attributes;

    // Iterate through the saved items
    for(const Json& item_json : temp)
    {   
        item = new Item;

        item->name = item_json["name"];

        // Get the attributes of this item
        item_attributes = item_json["attributes"];
    
        for(const std::string& attrib : item_attributes)
        {   
            item->attributes.push_back(attrib);
        }

        c->inventory.push_back(item);
    }

    return c;
}

Json SaveHandler::create_json_from_character(Character* c)
{
    Json character_save;

    character_save["name"] = c->name;
    character_save["race"] = c->race;
    character_save["character_class"] = c->character_class;
    character_save["height"] = c->height;
    character_save["weight"] = c->weight;
    character_save["speed"] = c->speed;
    character_save["description"] = c->description;
    character_save["hitpoints"] = c->hitpoints;
    character_save["max_hitpoints"] = c->max_hitpoints;
    character_save["mana"] = c->mana;
    character_save["max_mana"] = c->max_mana;

    Json temp;

    // Save Skills
    for(uint8_t i = 0; i < 14; ++i)
    {
        temp.push_back(c->skills.at(i));
    }

    character_save["skills"] = temp;
    temp.clear();

    // Save Attributes
    for(const std::string& _str : c->attributes)
    {
        temp.push_back(_str);
    }

    character_save["attributes"] = temp;
    temp.clear();

    // Save Effects
    for(const std::string& _str : c->effects)
    {
        temp.push_back(_str);
    }

    character_save["effects"] = temp;
    temp.clear();

    // Save Inventory
    
    Json json_item;

    Json attributes;

    for(Item* item : c->inventory)
    {
        attributes.clear();

        json_item["name"] = item->name;

        for(const std::string& attrib : item->attributes)
        {
            attributes.push_back(attrib);
        }

        json_item["attributes"] = attributes;

        character_save["inventory"].push_back(json_item);
    }

    return character_save;
}

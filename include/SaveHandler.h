#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include "Character.h"
#include "Json.h"

class SaveHandler
{

public:

    SaveHandler();

    void save_characters_to_disk(const std::vector<Character*>& characters);

    void delete_save_from_disk(const std::string& save_path);

    void unregister_active_save();

    bool create_new_save_file_on_disk(std::string file_name);

    const std::vector<std::string>& get_saves() const;

    std::vector<Character*> load_characters_from_save(std::string save_name);

private:

    std::string active_save_path;

    std::vector<std::string> save_paths;

    const static std::string SAVES_DIRECTORY;

    void fetch_saves_from_disk();

    Character* create_character_from_json(Json character_json);

    Json create_json_from_character(Character* c);
};

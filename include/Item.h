#pragma once

#include <string>
#include <vector>

struct Item 
{
    Item() {}

    Item(std::string _name, std::initializer_list<std::string> _attributes)
    {
        name = std::move(_name);

        attributes = _attributes;
    }

    Item(std::string _name, const std::vector<std::string>& _attributes)
    {
        name = std::move(_name);

        attributes = _attributes;
    }

    std::string name;
    std::vector<std::string> attributes;
};
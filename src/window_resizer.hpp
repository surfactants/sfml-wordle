#pragma once

#include <SFML/System/Vector2.hpp>

#include <box.hpp>

#include <string>

#include <map>
#include <vector>

class Window_Resizer {
public:
    Window_Resizer(std::map<char, Box>& keymap,
                   std::vector<std::vector<Box>>& boxes,
                   std::vector<std::string>& key_strings,
                   sf::Text& text_over);

    void operator() (const sf::Vector2u& wsize);

    unsigned int guess_rows { 0 };
    unsigned int guess_columns { 0 };

private:
    std::map<char, Box>& keymap;
    std::vector<std::vector<Box>>& boxes;
    std::vector<std::string>& key_strings;
    sf::Text& text_over;
};

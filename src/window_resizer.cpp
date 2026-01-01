#include "window_resizer.hpp"

#include <iostream>

Window_Resizer::Window_Resizer(std::map<char, Box>& keymap,
                               std::vector<std::vector<Box>>& boxes,
                               std::vector<std::string>& key_strings,
                               sf::Text& text_over)
    : keymap { keymap }
    , boxes { boxes }
    , key_strings { key_strings }
    , text_over { text_over }
{}

void Window_Resizer::operator() (const sf::Vector2u& wsize)
{
    sf::Vector2f center(wsize);
    center *= 0.5f;

    // BOXES
    const float box_factor = 12.f;
    const float dimension_box = wsize.y / box_factor;
    const float dimension_bpad = dimension_box / box_factor;

    const sf::Vector2f box_size(dimension_box, dimension_box);
    const sf::Vector2f box_padding(dimension_bpad, dimension_bpad);
    const sf::Vector2f box_offset(box_size + box_padding);

    const sf::Vector2f base_guess_pos(center.x, (-box_offset.y) + box_padding.y + (box_size.y * 0.5f));
    sf::Vector2f guess_pos(base_guess_pos);

    for (unsigned int i = 0; i < guess_rows; i++) {
        guess_pos.x = base_guess_pos.x;
        guess_pos.y += box_offset.y;
        for (unsigned int j = 0; j < guess_columns; j++) {
            guess_pos.x = base_guess_pos.x + ((static_cast<int>(j) - 2) * box_offset.x);
            std::cout << "box " << i << "-" << j << ": " << guess_pos.x << "x" << guess_pos.y << "\n";
            boxes[i][j].setSize(box_size);
            boxes[i][j].setPosition(guess_pos);
        }
    }

    // KEYS
    const float key_factor = 15.f;
    const float dimension_key = wsize.y / key_factor;
    const float dimension_kpad = dimension_key / (key_factor * .5f);

    const sf::Vector2f key_size(dimension_key, dimension_key);
    const sf::Vector2f key_padding(dimension_kpad, dimension_kpad);
    const sf::Vector2f key_offset(key_size + key_padding);

    sf::Vector2f key_pos(center.x, guess_pos.y + box_offset.y);//key_padding.y);

    for (const auto& key_row : key_strings) {
        const unsigned int key_count = key_row.size();

        key_pos.x = center.x;
        float x_offset = static_cast<float>(key_count - 1) * 0.5f;
        x_offset *= (key_size.x + key_padding.x);

        key_pos.x -= x_offset;

        for (unsigned int i = 0; i < key_count; i++) {
            char k = key_row[i];
            keymap[k].setSize(key_size);
            keymap[k].setPosition(key_pos);
            key_pos.x += key_offset.x;
        }
        key_pos.y += key_offset.y;
    }

    // TEXT_OVER
    constexpr static float font_factor { 24.f };
    unsigned int character_size = wsize.y / font_factor;
    text_over.setCharacterSize(character_size);

    sf::Vector2f text_pos(center.x, key_pos.y);
    text_pos.y += key_padding.y * 3.f;

    text_over.setPosition(text_pos);
}

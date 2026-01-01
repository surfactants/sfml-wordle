////////////////////////////////////////////////////////////
// Window_Resizer
// ----------
// Resizes and repositions elements in response to Resize events.
//
// LICENSE: zlib (https://www.zlib.net/zlib_license.html)
// -------
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include "window_resizer.hpp"

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

    const sf::Vector2f base_guess_pos(center.x, (-box_size.y * 0.5f));
    sf::Vector2f guess_pos(base_guess_pos);

    for (unsigned int i = 0; i < guess_rows; i++) {
        guess_pos.x = base_guess_pos.x;
        guess_pos.y += box_offset.y;
        for (unsigned int j = 0; j < guess_columns; j++) {
            guess_pos.x = base_guess_pos.x + ((static_cast<int>(j) - 2) * box_offset.x);
            boxes[i][j].setSize(box_size);
            boxes[i][j].setPosition(guess_pos);
        }
    }

    // KEYS
    const float key_factor = 15.f;
    const float dimension_key = wsize.y / key_factor;
    const float dimension_kpad = dimension_key / (key_factor * .2f);

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
    unsigned int character_size;
    if (wsize.x < wsize.y) {
        character_size = wsize.x / font_factor;
    }
    else {
        character_size = wsize.y / font_factor;
    }
    text_over.setCharacterSize(character_size);
    centerText(text_over);

    sf::Vector2f text_pos(center.x, key_pos.y);
    text_pos.y += key_padding.y * 3.f;

    text_over.setPosition(text_pos);
}

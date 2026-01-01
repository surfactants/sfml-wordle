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

#pragma once

#include <SFML/System/Vector2.hpp>

#include <box.hpp>

#include <string>

#include <map>
#include <vector>

/// \brief Resizes and repositions elements in response to Resize events.
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

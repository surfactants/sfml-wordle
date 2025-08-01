////////////////////////////////////////////////////////////
// GAME
// ----------
// Encapsulates and handles game logic and rendering.
// Written by surfactants (https://github.com/surfactants).
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

#include <box.hpp>

#include <functional>
#include <string>

#define UNICODE_a 97
#define UNICODE_z 122
#define UNICODE_A 65
#define UNICODE_Z 89

#define UNICODE_BACKSPACE 8
#define UNICODE_RETURN 13
#define UNICODE_CTRL_BACKSPACE 127

#define UNICODE_BACKTICK 96

////////////////////////////////////////////////////////////
/// \brief Main game container class, for handling the game itself.
///
class Game : public sf::Drawable {
public:
    Game() = delete;

    ////////////////////////////////////////////////////////////
    /// \brief Full constructor.
    ///
    Game(sf::RenderWindow& window);

    ////////////////////////////////////////////////////////////
    /// \brief Restarts the game.
    ///
    void reset();

    ////////////////////////////////////////////////////////////
    /// \brief Reads keyboard input.
    ///
    void readText(sf::Event& event);

    ////////////////////////////////////////////////////////////
    /// \brief Attempts to submit a guess.
    ///
    void enter();

    ////////////////////////////////////////////////////////////
    /// \brief Checks if there is an active game.
    ///
    /// \return playing (true if game is over)
    ///
    bool isPlaying();

    ////////////////////////////////////////////////////////////
    /// \brief Matches entered guess against the word list.
    ///
    void checkValid();

    ////////////////////////////////////////////////////////////
    /// \brief Used for resetting the game
    ///
    /// \param state -> valid
    ///
    void setValid(bool state);

    /// makeUppercase ///
    /// \brief Converts a string to all-uppercase.
    ///
    std::string makeUppercase(std::string str);

    static std::string font_file;

private:
    sf::Font font; /**<Main font for UI, same as menu class*/
    std::vector<std::string> words;
    std::string entered;
    std::string answer;

    sf::Color color_text;

    char alphabet[26];

    unsigned int guess;
    unsigned int letter;

    std::map<char, Box> keymap;

    bool playing;
    sf::Text text_over;

    std::vector<std::vector<Box>> boxes;

    bool valid;

    std::function<void()> closeWindow;

    static const unsigned int guess_rows { 6 };
    static const unsigned int guess_columns { 5 };

    ////////////////////////////////////////////////////////////
    /// \brief Draws the game to the render target.
    ///
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

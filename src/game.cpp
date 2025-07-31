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

#include <game.hpp>

#include <prng.hpp>

#include <fstream>

std::string Game::font_file;

Game::Game(sf::RenderWindow& window)
{
    std::string font_loc = "data/" + font_file;
    font.loadFromFile(font_loc);
    closeWindow = std::bind(sf::RenderWindow::close, &window);

    std::ifstream wlist("data/words.txt", std::ios::in);
    std::string word;
    while (std::getline(wlist, word)) {
        words.push_back(makeUppercase(word));
    }
    wlist.close();

    color_text = sf::Color(200,200,200);

    sf::Vector2f center(window.getSize());
    center /= 2.f;

    const float box_factor = 10.f;
    const float dimension_box = window.getSize().y / box_factor;
    const float dimension_bpad = dimension_box / box_factor;

    const sf::Vector2f box_size(dimension_box, dimension_box);
    const sf::Vector2f box_padding(dimension_bpad, dimension_bpad);
    const sf::Vector2f box_offset(box_size + box_padding);

    sf::Vector2f base_guess_pos(center.x, box_padding.y);
    base_guess_pos.x -= box_size.x / 2.f;
    base_guess_pos.x -= box_offset.x * 2.f;
    sf::Vector2f guess_pos(base_guess_pos);

    boxes.resize(guess_rows);
    for (unsigned int i = 0; i < guess_rows; i++) {
        boxes[i].resize(guess_columns);
        for (unsigned int j = 0; j < guess_columns; j++) {
            boxes[i][j].setFont(font);
            boxes[i][j].setSize(box_size);
            boxes[i][j].setPosition(guess_pos);
            guess_pos.x += box_offset.x;
        }
        guess_pos.x = base_guess_pos.x;
        guess_pos.y += box_offset.y;
    }

    std::vector<std::string> key_strings = {
        "QWERTYUIOP",
        "ASDFGHJKL",
        "ZXCVBNM"
    };

    const float key_factor = 15.f;
    const float dimension_key = window.getSize().y / key_factor;
    const float dimension_kpad = dimension_key / (key_factor * .5f);

    const sf::Vector2f key_size(dimension_key, dimension_key);
    const sf::Vector2f key_padding(dimension_kpad, dimension_kpad);
    const sf::Vector2f key_offset(key_size + key_padding);

    sf::Vector2f key_pos(center.x, guess_pos.y + key_padding.y);

    for (const auto& key_row : key_strings) {
        key_pos.x = center.x;
        const unsigned int key_count = key_row.size();
        const unsigned int half_count = key_count / 2;
        float x_offset;
        if (key_count % 2 == 0) { // even
            x_offset = half_count * key_size.x;
            x_offset += (static_cast<float>(half_count) + .5f) * key_padding.x;
        }
        else { // odd
            x_offset = (static_cast<float>(half_count) + .5f) * key_size.x;
            x_offset += half_count * key_padding.x;
        }

        key_pos.x -= x_offset;

        for (unsigned int i = 0; i < key_count; i++) {
            char k = key_row[i];
            keymap[k] = Box(key_row[i]);
            keymap[k].setFont(font);
            keymap[k].setSize(key_size);
            keymap[k].setPosition(key_pos);
            key_pos.x += key_offset.x;
        }
        key_pos.y += key_offset.y;
    }

    sf::Vector2f text_pos(center.x, key_pos.y);
    text_pos.y += key_padding.y * 3.f;

    const float font_factor = 20.f;
    unsigned int character_size = window.getSize().y / font_factor;
    text_over.setFont(font);
    text_over.setCharacterSize(character_size);
    text_over.setPosition(text_pos);
    text_over.setFillColor(color_text);

    reset();
}

void Game::reset()
{
    guess = 0;
    letter = 0;
    entered = "";
    for (unsigned int i = 0; i < boxes.size(); i++) {
        for (unsigned int j = 0; j < boxes[i].size(); j++) {
            boxes[i][j].reset();
            if (!valid) {
                boxes[i][j].setValid(true);
            }
        }
    }

    answer = words[prng::number(words.size())];

    playing = true;
    valid = true;

    for (auto& k : keymap) {
        char c = k.second.getChar();
        k.second.reset();
        k.second.setCharacter(c);
    }
}

void Game::readText(sf::Event& event)
{
    if (letter < guess_columns && ((event.text.unicode >= UNICODE_A && event.text.unicode <= UNICODE_Z) || (event.text.unicode >= UNICODE_a && event.text.unicode <= UNICODE_z))) {
        char c = toupper(static_cast<char>(event.text.unicode));
        entered.push_back(c);
        boxes[guess][letter].setCharacter(c);
        letter++;
        if (letter == guess_columns) {
            checkValid();
        }
    }
    else if (event.text.unicode == UNICODE_BACKSPACE && letter > 0) {
        letter--;
        boxes[guess][letter].reset();
        entered.pop_back();
        setValid(true);
    }
    else if (event.text.unicode == UNICODE_CTRL_BACKSPACE && letter > 0) {
        for (unsigned int i = 0; i < guess_columns; i++) {
            if (!valid) {
                boxes[guess][i].setValid(true);
            }
            boxes[guess][i].reset();
        }
        valid = true;
        entered = "";
        letter = 0;
    }
    else if (event.text.unicode == UNICODE_RETURN && letter == guess_columns) {
        enter();
    }
    else if (event.text.unicode == UNICODE_BACKTICK) {
        reset();
    }
}

void Game::checkValid()
{
    setValid(entered == answer || find(words.begin(), words.end(), entered) != words.end());
}

void Game::setValid(bool state)
{
    if (valid && !state) {
        for (unsigned int i = 0; i < boxes[guess].size(); i++) {
            boxes[guess][i].setValid(false);
        }
    }
    else if (!valid && state) {
        for (unsigned int i = 0; i < boxes[guess].size(); i++) {
            boxes[guess][i].setValid(true);
        }
    }
    valid = state;
}

std::string Game::makeUppercase(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

void Game::enter()
{
    if (valid) {
        std::map<char, int> correct;
        for (unsigned int i = 0; i < entered.length(); i++) {
            char ec = entered.at(i);
            correct[ec] += 0;
            if (correct[ec] == 0) {
                for (unsigned int j = 0; j < answer.length(); j++) {
                    if (answer.at(j) == entered.at(j) && answer.at(j) == ec) correct[ec]++;
                }
            }

            if (answer.find(ec) == std::string::npos) {
                boxes[guess][i].markWrong();
                keymap[ec].markWrong();
            }
            else {
                if (answer.at(i) == ec) {
                    boxes[guess][i].markRight();
                    keymap[ec].markRight();
                }
                else {
                    int acount = std::count(answer.begin(), answer.end(), ec);
                    if (acount - correct[ec]++ > 0) {
                        boxes[guess][i].markMaybe();
                        keymap[ec].markMaybe();
                    }
                }
            }
        }

        guess++;
        if (entered == answer) {
            playing = false;
            text_over.setString("You won! Press Enter to play again.");
            centerText(text_over);
        }
        else if (guess == guess_rows) {
            playing = false;
            text_over.setString("Answer was " + answer + "... Press Enter to play again.");
            centerText(text_over);
        }
        letter = 0;
        entered = "";
    }
}

bool Game::isPlaying()
{
    return playing;
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& row : boxes) {
        for (const auto& box : row) {
            target.draw(box, states);
        }
    }

    if (!playing) {
        target.draw(text_over, states);
    }

    for (const auto& k : keymap) {
        target.draw(k.second, states);
    }
}

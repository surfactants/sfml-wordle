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

#include <iostream>

std::string Game::font_file;


std::vector<std::string> Game::key_strings = {
    "QWERTYUIOP",
    "ASDFGHJKL",
    "ZXCVBNM"
};

Game::Game(sf::RenderWindow& window)
    : resize { keymap, boxes, key_strings, text_over }
{
    resize.guess_rows = guess_rows;
    resize.guess_columns = guess_columns;

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

    text_over.setFont(font);
    text_over.setFillColor(color_text);

    // make boxes
    boxes.resize(guess_rows);
    for (unsigned int i = 0; i < guess_rows; i++) {
        boxes[i].resize(guess_columns);
        for (unsigned int j = 0; j < guess_columns; j++) {
            boxes[i][j].setFont(font);
        }
    }

    // make keys
    for (const auto& key_row : key_strings) {
        const unsigned int key_count = key_row.size();
        for (unsigned int i = 0; i < key_count; i++) {
            char k = key_row[i];
            keymap[k] = Box(key_row[i]);
            keymap[k].setFont(font);
        }
    }

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
                    if (answer.at(j) == entered.at(j) && answer.at(j) == ec) {
                        correct[ec]++;
                    }
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

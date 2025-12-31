////////////////////////////////////////////////////////////
// SHELL
// ----------
// External abstraction layer for SFML programs.
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

#include <shell.hpp>

#include <fstream>

#include <iostream>

const std::string Config::COLORBLIND = "COLORBLIND";
const std::string Config::FONT = "FONT";
const std::string Config::FULLSCREEN = "FULLSCREEN";

const std::string Shell::window_name = "NOT-wordle";

Shell::Shell()
    : window { sf::VideoMode(), window_name, sf::Style::Fullscreen, sf::ContextSettings(0, 0, 4) }
{
    view.setSize(sf::Vector2f(window.getSize()));
    view.setCenter(sf::Vector2f(window.getSize()) / 2.f);

    readConfig();

    game = std::make_unique<Game>(window);
}

void Shell::run()
{
    while (window.isOpen()) {
        input();
        draw();
    }
}

void Shell::input()
{
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) { // KEY PRESS
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        else if (event.type == sf::Event::TextEntered) { // TEXT ENTERED
            if (game->isPlaying()) {
                game->readText(event);
            }
            else if (event.text.unicode == UNICODE_RETURN) {
                game->reset();
            }
        }
        else if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Shell::readConfig()
{
    const std::string config_file = "config.txt";
    std::ifstream config_in(config_file, std::ios::in);
    std::string line;
    auto read = [](const std::string& line) {
        return line.substr(0, line.find('='));
    };
    while (std::getline(config_in, line)) {
        std::string key = read(line);
        if (key == Config::COLORBLIND) {
            if (line.find('1') != std::string::npos) {
                loadColorblindPalette();
            }
        }
        else if (key == Config::FONT) {
            Game::font_file = line.substr(line.find('=') + 1);
        }
        else if (key == Config::FULLSCREEN) {
            std::cout << "found fullscreen line\n";
            if (line.find('0') != std::string::npos) {
                std::cout << "switching to not-fullscreen\n";
                window.create(sf::VideoMode(800, 600), window_name, sf::Style::Resize, sf::ContextSettings(0, 0, 4));
            }
        }
    }
}

void Shell::loadColorblindPalette()
{
    // the colorblind palette, as found here: https://davidmathlogic.com/colorblind/
    // (the page on ibm's website to which that page links is no longer there)
    Box::color_wrong = sf::Color(220, 38, 127); // ibm pink
    Box::color_invalid = Box::color_wrong;
    Box::color_maybe = sf::Color(255, 176, 0); // ibm yellow
    Box::color_right = sf::Color(100, 143, 255); // ibm blue
}

void Shell::draw()
{
    window.clear();
        window.setView(view);
        window.draw(*game);
    window.display();
}

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

Shell::Shell()
    : window { sf::VideoMode(), "treeviz", sf::Style::Fullscreen, sf::ContextSettings(0, 0, 4) }
{
    view.setSize(sf::Vector2f(window.getSize()));
    view.setCenter(sf::Vector2f(window.getSize()) / 2.f);

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

void Shell::draw()
{
    window.clear();
        window.setView(view);
        window.draw(*game);
    window.display();
}

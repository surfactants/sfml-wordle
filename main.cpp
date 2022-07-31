////////////////////////////////////////////////////////////
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include <game.hpp>

int main(){
    randomSeed();

    sf::RenderWindow window(sf::VideoMode(), "wordle", sf::Style::Fullscreen);

    Game mainGame(window);

    while(window.isOpen()){ //MAIN WINDOW LOOP
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::MouseMoved) mainGame.checkMouse();
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left) mainGame.click();
            }
            if(event.type == sf::Event::Closed){
                window.close();
                return 0;
            }
            else if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape) window.close();
            }
            else if(event.type == sf::Event::TextEntered){
                if(mainGame.isPlaying()) mainGame.readText(event);
                else if(event.text.unicode == UNICODE_RETURN) mainGame.reset();
            }
        }

        window.clear();

        window.draw(mainGame);

        window.display();
    }
}

#include "game.h"

int main(){
    randomSeed();

    sf::RenderWindow window(sf::VideoMode(), "name", sf::Style::Fullscreen);

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
    return 0;
}

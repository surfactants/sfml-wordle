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

Game::Game(sf::RenderWindow& newWindow) : window{ newWindow }{
    font.loadFromFile("data/iosevka-fixed-bold.ttf");

    std::ifstream wlist("data/words.txt", std::ios::in);

    std::string word;
    while(std::getline(wlist, word)){
        words.push_back(makeUppercase(word));
    }
    wlist.close();

    color_text = sf::Color(200,200,200);

    boxes.resize(6);

    sf::Vector2f size_box(84, 84);

    sf::Vector2f spos(size_box.x/2 + 128, 16);
    sf::Vector2f pos = spos;
    sf::Vector2f offset(size_box.x + 8, size_box.y + 16);

    for(unsigned int i=0; i<boxes.size(); i++){
        boxes[i].resize(5);
        for(unsigned int j=0; j<boxes[i].size(); j++){
            boxes[i][j].setFont(font);
            boxes[i][j].setPosition(pos);
            boxes[i][j].setSize(size_box);
            pos.x += offset.x;
        }
        pos.x = spos.x;
        pos.y += offset.y;
    }

    std::string keyString = "QWERTYUIOPASDFGHJKLZXCVBNM";

    sf::Vector2f size_key(60, 60);
    offset = size_key + sf::Vector2f(4,4);

    pos.x = spos.x - offset.x * 1.5;

    for(unsigned int i = 0; i < keyString.size(); i++){
        char k = keyString[i];
        keymap[k] = new Box(keyString[i]);
        keymap[k]->setFont(font);
        keymap[k]->setPosition(pos);
        keymap[k]->setSize(size_key);
        if(k == 'P' || k == 'L' || k == 'M'){
            if(k == 'P'){
                pos.x = spos.x - offset.x;
            }
            else if(k == 'L'){
                pos.x = spos.x - offset.x/2;
            }
            else if(k == 'M'){
                pos.x = spos.x;
            }
            pos.y += offset.y;
        }
        else pos.x += offset.x;
    }

    pos.x = spos.x;

    text_over.setFont(font);
    text_over.setCharacterSize(48);
    text_over.setPosition(pos);
    text_over.setFillColor(color_text);

    pos.y += offset.y;

    button_reset.setPosition(pos);

    pos.x += offset.x * 3;

    button_quit.setPosition(pos);

    reset();
}

Game::~Game(){
    for(auto& k : keymap){
        delete k.second;
    }
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(unsigned int i=0; i<boxes.size(); i++){
        for(unsigned int j=0; j<boxes[i].size(); j++){
            target.draw(boxes[i][j], states);
        }
    }
    if(!playing) target.draw(text_over, states);

    target.draw(button_reset, states);
    target.draw(button_quit, states);

    for(auto& k : keymap){
        target.draw(*k.second, states);
    }
}

void Game::checkMouse(){
    button_reset.checkHighlight();
    button_quit.checkHighlight();
}

void Game::reset(){
    guess = 0;
    letter = 0;
    entered = "";
    for(unsigned int i=0; i<boxes.size(); i++){
        for(unsigned int j=0; j<boxes[i].size(); j++){
            boxes[i][j].reset();
            if(!valid) boxes[i][j].setValid(true);
        }
    }

    answer = words[randomInteger(0, words.size()-1)];

    playing = true;
    valid = true;

    for(auto& k : keymap){
        char c = k.second->getChar();
        k.second->reset();
        k.second->setCharacter(c);
    }
}

void Game::readText(sf::Event& event){
    if(letter < 5 && ((event.text.unicode >= UNICODE_A && event.text.unicode <= UNICODE_Z) || (event.text.unicode >= UNICODE_a && event.text.unicode <= UNICODE_z))){
        char c = toupper(static_cast<char>(event.text.unicode));
        entered.push_back(c);
        boxes[guess][letter].setCharacter(c);
        letter++;
        if(letter == 5) checkValid();
    }
    else if(event.text.unicode == UNICODE_BACKSPACE && letter > 0){
        letter--;
        boxes[guess][letter].reset();
        entered.pop_back();
        setValid(true);
    }
    else if(event.text.unicode == UNICODE_CTRL_BACKSPACE && letter > 0){
        for(unsigned int i=0; i<5; i++){
            if(!valid) boxes[guess][i].setValid(true);
            boxes[guess][i].reset();
        }
        valid = true;
        entered = "";
        letter = 0;
    }
    else if(event.text.unicode == UNICODE_RETURN && letter == 5) enter();
    else if(event.text.unicode == 96) reset();
}

void Game::checkValid(){
    setValid(entered==answer || find(words.begin(), words.end(), entered) != words.end());
}

void Game::setValid(bool state){
    if(valid && !state){
        for(unsigned int i=0; i<boxes[guess].size(); i++){
            boxes[guess][i].setValid(false);
        }
    }
    else if(!valid && state){
        for(unsigned int i=0; i<boxes[guess].size(); i++){
            boxes[guess][i].setValid(true);
        }
    }
    valid = state;
}

void Game::enter(){
    if(valid){
        std::map<char, int> correct;
        for(unsigned int i=0; i<entered.length(); i++){
            char ec = entered.at(i);
            correct[ec] += 0;
            if(correct[ec] == 0){
                for(unsigned int j=0; j<answer.length(); j++){
                    if(answer.at(j) == entered.at(j) && answer.at(j) == ec) correct[ec]++;
                }
            }

            if(answer.find(ec) == std::string::npos){
                boxes[guess][i].markWrong();
                keymap[ec]->markWrong();
            }
            else{
                if(answer.at(i) == ec){
                    boxes[guess][i].markRight();
                    keymap[ec]->markRight();
                }
                else{
                    int acount = std::count(answer.begin(), answer.end(), ec);
                    if(acount - correct[ec]++ > 0){
                        boxes[guess][i].markMaybe();
                        keymap[ec]->markMaybe();
                    }
                }
            }
        }

        guess++;
        if(entered == answer){
            playing = false;
            text_over.setString("You won!");
        }
        else if(guess == 6){
            playing = false;
            text_over.setString("Answer was " + answer);
        }
        letter = 0;
        entered = "";
    }
}

bool Game::isPlaying(){
    return playing;
}

void Game::click(){
    if(button_reset.isHighlighted()) reset();
    else if(button_quit.isHighlighted()) window.close();
}

///////////////////////////////////
//END GAME IMPLEMENTATION
///////////////////////////////////

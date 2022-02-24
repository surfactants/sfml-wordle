#include "game.h"

///////////////////////////////////
//BEGIN BOX IMPLEMENTATION
///////////////////////////////////
sf::Color Box::color_empty = sf::Color(180,180,180);
sf::Color Box::color_wrong = sf::Color(255,150,150);
sf::Color Box::color_maybe = sf::Color(255,255,180);
sf::Color Box::color_right = sf::Color(150,255,150);
sf::Color Box::color_text = sf::Color(50,50,50);
sf::Color Box::color_invalid = sf::Color(255,100,100);

float Box::radius_box = 3;

Box::Box(){
    character.setFillColor(color_text);
    character.setCharacterSize(64);

    box.setCornerPointCount(points_box);
    box.setCornersRadius(radius_box);
}

Box::Box(char c){
    character.setFillColor(color_text);
    character.setCharacterSize(64);

    box.setCornerPointCount(points_box);
    box.setCornersRadius(radius_box);
    setCharacter(c);
}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(box, states);
    target.draw(character, states);
}

void Box::setFont(sf::Font& font){
    character.setFont(font);
}

void Box::setSize(sf::Vector2f siz){
    box.setSize(siz);
    box.setOrigin(sf::Vector2f(siz.x/2, 0));
    character.setCharacterSize(siz.x * 0.7);
    character.setOrigin(sf::Vector2f(character.getLocalBounds().width/2, 0));
    character.setPosition(box.getPosition());
}

void Box::setPosition(sf::Vector2f pos){
    box.setPosition(pos);
    pos.x += box.getSize().x/4;
    character.setPosition(pos);
}

void Box::reset(){
    box.setFillColor(color_empty);
    character.setString("");
}

void Box::setCharacter(char c){
    character.setString(c);
    character.setOrigin(sf::Vector2f(character.getLocalBounds().width/2, 0));
    character.setPosition(box.getPosition());
}

void Box::markWrong(){
    box.setFillColor(color_wrong);
}

void Box::markMaybe(){
    box.setFillColor(color_maybe);
}

void Box::markRight(){
    box.setFillColor(color_right);
}

void Box::setValid(bool valid){
    if(valid) character.setFillColor(color_text);
    else character.setFillColor(color_invalid);
}

char Box::getChar(){
    std::string c = character.getString();
    return c[0];
}

///////////////////////////////////
//BEGIN BUTTON IMPLEMENTATION
///////////////////////////////////

sf::Color Button::color_fill = sf::Color(125,125,125);
sf::Color Button::color_highlight = sf::Color(225,225,225);

Button::Button(sf::Font& font, std::string title){
    text.setFont(font);
    text.setString(title);
    text.setCharacterSize(48);
    box.setCornerPointCount(5);
    box.setCornersRadius(5);

    unhighlight();

}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(box, states);
    target.draw(text, states);
}

void Button::setPosition(sf::Vector2f pos){
    box.setPosition(pos);

    sf::Vector2f bsize(text.getLocalBounds().width + text.getCharacterSize()/2, text.getCharacterSize() * 1.45);
    box.setSize(bsize);

    text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2, 0));
    pos.x += bsize.x/2;
    text.setPosition(pos);
}

void Button::checkHighlight(){
    if(!highlighted && box.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)){
        highlight();
    }
    else if(highlighted && !box.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)){
        unhighlight();
    }
}

bool Button::isHighlighted(){
    return highlighted;
}

void Button::highlight(){
    highlighted = true;
    box.setFillColor(color_highlight);
    text.setFillColor(color_fill);
}

void Button::unhighlight(){
    highlighted = false;
    box.setFillColor(color_fill);
    text.setFillColor(color_highlight);
}

///////////////////////////////////
//BEGIN GAME IMPLEMENTATION
///////////////////////////////////

Game::Game(sf::RenderWindow& newWindow) : window{ newWindow }{
    font.loadFromFile("data/iosevka-fixed-bold.ttf");

    std::ifstream wlist("data/words.txt", std::ios::in);

    std::string word;
    while(std::getline(wlist, word)){
        words.push_back(makeUppercase(word));
    }
    wlist.close();

    color_text = sf::Color(150,150,150);

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

    keys.push_back(Box('Q'));
    keys.push_back(Box('W'));
    keys.push_back(Box('E'));
    keys.push_back(Box('R'));
    keys.push_back(Box('T'));
    keys.push_back(Box('Y'));
    keys.push_back(Box('U'));
    keys.push_back(Box('I'));
    keys.push_back(Box('O'));
    keys.push_back(Box('P'));
    keys.push_back(Box('A'));
    keys.push_back(Box('S'));
    keys.push_back(Box('D'));
    keys.push_back(Box('F'));
    keys.push_back(Box('G'));
    keys.push_back(Box('H'));
    keys.push_back(Box('J'));
    keys.push_back(Box('K'));
    keys.push_back(Box('L'));
    keys.push_back(Box('Z'));
    keys.push_back(Box('X'));
    keys.push_back(Box('C'));
    keys.push_back(Box('V'));
    keys.push_back(Box('B'));
    keys.push_back(Box('N'));
    keys.push_back(Box('M'));

    sf::Vector2f size_key(60, 60);
    offset = size_key + sf::Vector2f(4,4);

    pos.x = spos.x - offset.x * 1.5;

    for(unsigned int i = 0; i < keys.size(); i++){
        keys[i].setFont(font);
        keys[i].setPosition(pos);
        keys[i].setSize(size_key);
        char k = keys[i].getChar();
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
        keymap.insert(std::make_pair(k, &keys[i]));
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

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(unsigned int i=0; i<boxes.size(); i++){
        for(unsigned int j=0; j<boxes[i].size(); j++){
            target.draw(boxes[i][j], states);
        }
    }
    if(!playing) target.draw(text_over, states);

    target.draw(button_reset, states);
    target.draw(button_quit, states);

    for(unsigned int i=0; i<keys.size(); i++){
        target.draw(keys[i], states);
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

    for(unsigned int i=0; i<keys.size(); i++){
        char c = keys[i].getChar();
        keys[i].reset();
        keys[i].setCharacter(c);
    }

}

void Game::readText(sf::Event& event){

    //RETURN = 13
    //BACKSPACE = 8
    //CTRL BACKSPACE = 127;

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
        while(letter > 0){
            boxes[guess][--letter].reset();
            entered.pop_back();
        }
        entered.pop_back();
    }
    else if(event.text.unicode == UNICODE_RETURN && letter == 5) enter();
    else if(event.text.unicode == 96) reset();
}

void Game::checkValid(){
    setValid(find(words.begin(), words.end(), entered) != words.end());
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
        for(unsigned int i=0; i<entered.length(); i++){
            char ec = entered.at(i);
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
                    boxes[guess][i].markMaybe();
                    keymap[ec]->markMaybe();
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

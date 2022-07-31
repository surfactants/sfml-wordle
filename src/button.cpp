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

#include <button.hpp>

sf::Color Button::color_fill = sf::Color(125,125,125);
sf::Color Button::color_highlight = sf::Color(225,225,225);

float Button::radius_box = 3;

Button::Button(sf::Font& font, std::string title){
    text.setFont(font);
    text.setString(title);
    text.setCharacterSize(size_char);
    box.setCornerPointCount(points_box);
    box.setCornersRadius(radius_box);

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

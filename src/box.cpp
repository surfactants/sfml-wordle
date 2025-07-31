////////////////////////////////////////////////////////////
// BOX
// ----------
// Displays a single letter in a frame.
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

#include <box.hpp>

void centerText(sf::Text& text)
{
    sf::FloatRect trect = text.getLocalBounds();
    text.setOrigin(trect.left + trect.width / 2.f, trect.top + trect.height / 2.f);
}

sf::Color Box::color_empty = sf::Color(180,180,180);
sf::Color Box::color_wrong = sf::Color(255,150,150);
sf::Color Box::color_maybe = sf::Color(255,255,180);
sf::Color Box::color_right = sf::Color(150,255,150);
sf::Color Box::color_text = sf::Color(50,50,50);
sf::Color Box::color_invalid = sf::Color(255,100,100);

float Box::radius_box = 3;

Box::Box()
{
    character.setFillColor(color_text);

    box.setCornerPointCount(points_box);
    box.setCornersRadius(radius_box);
}

Box::Box(char c)
{
    character.setFillColor(color_text);

    box.setCornerPointCount(points_box);
    box.setCornersRadius(radius_box);
    setCharacter(c);
}

void Box::setFont(sf::Font& font)
{
    character.setFont(font);
}

void Box::setSize(sf::Vector2f size)
{
    box.setSize(size);
    box.setOrigin(sf::Vector2f(size.x/2, 0));
    character.setCharacterSize(size.x * 0.7);
    character.setPosition(box.getPosition());
    centerText(character);
}

void Box::setPosition(sf::Vector2f pos)
{
    box.setPosition(pos);
    pos.x += box.getSize().x/4;
    character.setPosition(pos);
}

void Box::reset()
{
    box.setFillColor(color_empty);
    character.setString("");
}

void Box::setCharacter(char c)
{
    character.setString(c);
    character.setOrigin(sf::Vector2f(character.getLocalBounds().width/2, 0));
    character.setPosition(box.getPosition());
}

void Box::markWrong()
{
    box.setFillColor(color_wrong);
}

void Box::markMaybe()
{
    box.setFillColor(color_maybe);
}

void Box::markRight()
{
    box.setFillColor(color_right);
}

void Box::setValid(bool valid)
{
    if (valid) {
        character.setFillColor(color_text);
    }
    else {
        character.setFillColor(color_invalid);
    }
}

char Box::getChar()
{
    std::string c = character.getString();
    return c[0];
}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const\
{
    target.draw(box, states);
    target.draw(character, states);
}

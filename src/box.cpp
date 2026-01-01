////////////////////////////////////////////////////////////
// Box
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

const sf::Color Box::color_text = sf::Color(244, 244, 244);
const sf::Color Box::color_outline = Box::color_text;
const sf::Color Box::color_empty = sf::Color(11, 11, 11);

sf::Color Box::color_wrong = sf::Color(244, 55, 55);
sf::Color Box::color_invalid = Box::color_wrong;
sf::Color Box::color_maybe = sf::Color(233, 233, 55);
sf::Color Box::color_right = sf::Color(77, 202, 77);


const float Box::outline_thickness { 2.f };

const float Box::radius_box { 2.f };

Box::Box()
{
    character.setFillColor(color_text);
    character.setOutlineColor(color_empty);
    character.setOutlineThickness(outline_thickness);

    box.setOutlineColor(color_outline);
    box.setOutlineThickness(outline_thickness);

    box.setCornerPointCount(points_box);
    box.setCornersRadius(radius_box);
}

Box::Box(char c)
{
    character.setFillColor(color_text);
    character.setOutlineColor(color_empty);
    character.setOutlineThickness(outline_thickness);

    box.setOutlineColor(color_outline);
    box.setOutlineThickness(outline_thickness);

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
    box.setOrigin(size * 0.5f);
    character.setCharacterSize(size.x * 0.5);
    centerText(character);
}

void Box::setPosition(sf::Vector2f pos)
{
    box.setPosition(pos);
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
    centerText(character);
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

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

#pragma once

#include <SFML/Graphics.hpp>

#include <roundedRectangle.hpp>

/// \brief sets a text object's origin to the center of its local frame bounds
void centerText(sf::Text& text);

/// \brief For holding guesses, and the on-screen keyboard.
class Box : public sf::Drawable {
public:
    static sf::Color color_wrong;
    static sf::Color color_invalid;
    static sf::Color color_maybe;
    static sf::Color color_right;

    /// \brief Default constructor.
    Box();

    /// \brief Secondary constructor for keys.
    /// \param c -> setCharacter()
    Box(char c);

    /// \brief Sets the character font
    /// \param font -> character.setFont()
    void setFont(sf::Font& font);

    /// \brief Sets the size of the box, and calculates text size.
    /// \param siz -> box.setSize(), siz.x -> character.setCharacterSize()
    void setSize(sf::Vector2f size);

    /// \brief Places the box and text.
    /// \param pos -> box.setPosition() -> character.setPosition()
    void setPosition(sf::Vector2f pos);

    /// \brief Clears entered character and resets the color.
    void reset();

    /// \brief Sets the character text's string.
    /// \param c -> character.setString()
    void setCharacter(char c);

    /// \brief Sets color to indicate a letter is wrong.
    void markWrong();

    /// \brief Sets color to indicate a letter is correct, but misplaced.
    void markMaybe();

    /// \brief Sets color to indicate a letter is correct.
    void markRight();

    /// \brief Sets text color based on validity of entered word.
    /// \param valid -> character.setFillColor()
    void setValid(bool valid);

    /// \brief Returns the text string's character
    /// \return character.getString()
    char getChar();

//private:
    static const sf::Color color_text;
    static const sf::Color color_outline;
    static const sf::Color color_empty;

    static const float outline_thickness;
    static const int points_box { 5 };
    static const float radius_box;

    sf::RoundedRectangleShape box;
    sf::Text character;

    /// \brief Draws the box and text to the render target.
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


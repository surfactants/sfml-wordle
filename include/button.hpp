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

#pragma once

#include <SFML/Graphics.hpp>
#include <roundedRectangle.hpp>

////////////////////////////////////////////////////////////
/// \brief Clickable buttons
///
class Button : public sf::Drawable{
private:
    static sf::Color color_fill;
    static sf::Color color_highlight;

    sf::RoundedRectangleShape box;
    sf::Text text;
    bool highlighted;

    const static int size_char = 48;
    const static int points_box = 5;
    static float radius_box;
public:

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// \param font -> text.setFont()
    /// \param title -> text.setString()
    ///
    Button(sf::Font& font, std::string title);

    ////////////////////////////////////////////////////////////
    /// \brief Draws the box and text to the render target.
    ///
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    ////////////////////////////////////////////////////////////
    /// \brief Places the box and text.
    ///
    /// \param pos -> box.setPosition() -> text.setPosition()
    void setPosition(sf::Vector2f pos);

    ////////////////////////////////////////////////////////////
    /// \brief Checks if the box's global bounds contain the mouse.
    ///
    void checkHighlight();

    ////////////////////////////////////////////////////////////
    /// \brief Returns the highlighted state.
    ///
    /// \return highlighted
    ///
    bool isHighlighted();

    ////////////////////////////////////////////////////////////
    /// \brief Sets highlight to true and changes colors accordingly.
    ///
    void highlight();

    ////////////////////////////////////////////////////////////
    /// \brief Sets highlight to false and changes colors accordingly.
    ///
    void unhighlight();
};


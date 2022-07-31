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
#include <random>
#include <fstream>

    ////////////////////////////////////////////////////////////
    /// \brief Seeds the random number generator.
    /// To be run once, at the beginning of int main()
    ///
    /// \see randomInteger(), randomFloat(), randomBool(), weightedBool()
    ///
    ////////////////////////////////////////////////////////////
    void randomSeed();

    ////////////////////////////////////////////////////////////
    /// \brief Returns a random whole number between floor and ceil.
    ///
    /// \param \b floor the lowest possible result
    /// \param \b ceil the highest possible result
    ///
    /// \return random
    ///
    /// \see randomFloat(), randomBool(), weightedBool()
    ///
    ////////////////////////////////////////////////////////////
    int randomInteger(int floor, int ceil);

    ////////////////////////////////////////////////////////////
    /// \brief Converts a string to all-uppercase.
    ///
    /// \param \b str
    ///
    /// \return \b str
    ///
    /// \see capitalize()
    ///
    ////////////////////////////////////////////////////////////
    std::string makeUppercase(std::string str);

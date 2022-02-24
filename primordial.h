#ifndef FUNC_PRIMORDIAL
#define FUNC_PRIMORDIAL

#include <SFML/Graphics.hpp>
#include "roundedRectangle.hpp"
#include <random>
#include <fstream>

    ////////////////////////////////////////////////////////////
    /// \brief Seeds the random number generator.
    /// To be run once, at the beginning of int main()
    ///
    /// \see randomInteger()
    ///
    void randomSeed();

    ////////////////////////////////////////////////////////////
    /// \brief Returns a random whole number between floor and ceil.
    ///
    /// \param \b floor the lowest possible result
    /// \param \b ceil the highest possible result
    ///
    /// \return random
    ///
    /// \see randomSeed()
    ///
    int randomInteger(int floor, int ceil);

    ////////////////////////////////////////////////////////////
    /// \brief Converts a string to all-uppercase.
    ///
    /// \param \b str ->std::transform
    ///
    /// \return \b str
    ///
    std::string makeUppercase(std::string str);
#endif

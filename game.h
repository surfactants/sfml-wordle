#ifndef GAME_H
#define GAME_H
#include "primordial.h"

#define UNICODE_a 97
#define UNICODE_z 122
#define UNICODE_A 65
#define UNICODE_Z 89

#define UNICODE_BACKSPACE 8
#define UNICODE_RETURN 13
#define UNICODE_CTRL_BACKSPACE 127

////////////////////////////////////////////////////////////
/// \brief For holding guesses, and the on-screen keyboard.
///
class Box : public sf::Drawable{
private:
    static sf::Color color_empty;
    static sf::Color color_wrong;
    static sf::Color color_maybe;
    static sf::Color color_right;
    static sf::Color color_text;
    static sf::Color color_invalid;

    const static int points_box = 5;
    static float radius_box;

    sf::RoundedRectangleShape box;
    sf::Text character;
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    Box();

    ////////////////////////////////////////////////////////////
    /// \brief Secondary constructor for keys.
    ///
    /// \param c -> setCharacter()
    ///
    Box(char c);

    ////////////////////////////////////////////////////////////
    /// \brief Draws the box and text to the render target.
    ///
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    ////////////////////////////////////////////////////////////
    /// \brief Sets the character font
    ///
    /// \param font -> character.setFont()
    ///
    void setFont(sf::Font& font);

    ////////////////////////////////////////////////////////////
    /// \brief Sets the size of the box, and calculates text size.
    ///
    /// \param siz -> box.setSize(), siz.x -> character.setCharacterSize()
    ///
    void setSize(sf::Vector2f siz);

    ////////////////////////////////////////////////////////////
    /// \brief Places the box and text.
    ///
    /// \param pos -> box.setPosition() -> character.setPosition()
    ///
    void setPosition(sf::Vector2f pos);

    ////////////////////////////////////////////////////////////
    /// \brief Clears entered character and resets the color.
    ///
    void reset();

    ////////////////////////////////////////////////////////////
    /// \brief Sets the character text's string.
    ///
    /// \param c -> character.setString()
    ///
    void setCharacter(char c);

    ////////////////////////////////////////////////////////////
    /// \brief Sets color to indicate a letter is wrong.
    ///
    void markWrong();

    ////////////////////////////////////////////////////////////
    /// \brief Sets color to indicate a letter is correct, but misplaced.
    ///
    void markMaybe();

    ////////////////////////////////////////////////////////////
    /// \brief Sets color to indicate a letter is correct.
    ///
    void markRight();

    ////////////////////////////////////////////////////////////
    /// \brief Sets text color based on validity of entered word.
    ///
    /// \param valid -> character.setFillColor()
    ///
    void setValid(bool valid);

    ////////////////////////////////////////////////////////////
    /// \brief Returns the text string's character
    ///
    /// \return character.getString()
    ///
    char getChar();
};

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

////////////////////////////////////////////////////////////
/// \brief Main game container class, for handling the game itself.
///
class Game : public sf::Drawable{
private:
    sf::RenderWindow& window;
    sf::Font font; /**<Main font for UI, same as menu class*/
    std::vector<std::string> words;
    std::string entered;
    std::string answer;


    sf::Color color_text;

    char alphabet[26];

    unsigned int guess;
    unsigned int letter;

    std::vector<Box> keys;
    std::map<char, Box*> keymap;

    bool playing;
    sf::Text text_over;

    Button button_reset{font, "reset"};
    Button button_quit{font, "quit"};

    std::vector<std::vector<Box>> boxes;

    bool valid;
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// \param \b &newWindow -> window
    ///
    Game(sf::RenderWindow& newWindow);

    ////////////////////////////////////////////////////////////
    /// \brief Draws the game to the render target.
    ///
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    ////////////////////////////////////////////////////////////
    /// \brief Checks button highlights.
    ///
    void checkMouse();

    ////////////////////////////////////////////////////////////
    /// \brief Restarts the game.
    ///
    void reset();

    ////////////////////////////////////////////////////////////
    /// \brief Reads keyboard input.
    ///
    void readText(sf::Event& event);

    ////////////////////////////////////////////////////////////
    /// \brief Attempts to submit a guess.
    ///
    void enter();

    ////////////////////////////////////////////////////////////
    /// \brief Checks if there is an active game.
    ///
    /// \return playing (true if game is over)
    ///
    bool isPlaying();

    ////////////////////////////////////////////////////////////
    /// \brief Checks if a button was clicked.
    ///
    void click();

    ////////////////////////////////////////////////////////////
    /// \brief Matches entered guess against the word list.
    ///
    void checkValid();

    ////////////////////////////////////////////////////////////
    /// \brief Used for resetting the game
    ///
    /// \param state -> valid
    ///
    void setValid(bool state);
};

#endif // GAME_H

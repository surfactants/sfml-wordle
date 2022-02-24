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
    Box();
    Box(char c);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setFont(sf::Font& font);
    void setSize(sf::Vector2f siz);
    void setPosition(sf::Vector2f pos);
    void reset();
    void setCharacter(char c);
    void markWrong();
    void markMaybe();
    void markRight();
    void setValid(bool valid);
    char getChar();
};

class Button : public sf::Drawable{
private:
    static sf::Color color_fill;
    static sf::Color color_highlight;

    sf::RoundedRectangleShape box;
    sf::Text text;
    bool highlighted;
public:
    Button(sf::Font& font, std::string title);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setPosition(sf::Vector2f pos);
    void checkHighlight();
    bool isHighlighted();
    void highlight();
    void unhighlight();
};

////////////////////////////////////////////////////////////
/// \brief Main game container class, for handling the game itself.
///
////////////////////////////////////////////////////////////
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
    ////////////////////////////////////////////////////////////
    Game(sf::RenderWindow& newWindow);

    ////////////////////////////////////////////////////////////
    /// \brief Draws the game to the render target.
    ///
    ////////////////////////////////////////////////////////////
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void checkMouse();

    void reset();

    void readText(sf::Event& event);

    void enter();

    bool isPlaying();

    void click();

    void checkValid();
    void setValid(bool state);
};

#endif // GAME_H

# SFML Wordle Clone
## About
Written by [surfactants](github.com/surfactants)

Compiled with GCC 11.2.0, using SFML 2.5.1

Optimized for 1080p.

Only natively released for Windows.

## Controls
`ctrl + backspace` deletes the whole entry.

`return` inputs a guess, or restarts the game if it has ended.

`escape` exits the game.

``backtick/tilde (`/~)`` starts a new game.

The keyboard isn't clickable: it's just there to track letters.

## Notes
Word list is a lightly edited version of Alan Beale's 12Dicts American 2of12inf list, version 6.0.2:  
http://wordlist.aspell.net/12dicts/  
Edits include removing archaic/obsolete words, slurs, a couple words I plain don't like, and a few inexplicable british english formes. Some words were added.

RoundedRectangleShape class was written by Rémi Bèges, from the SFML wiki:  
https://github.com/SFML/SFML/wiki/Source:-Draw-Rounded-Rectangle

Font is Iosevka:  
https://github.com/be5invis/iosevka

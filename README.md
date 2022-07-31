# SFML Wordle Clone

Compiled with GCC 11.2.0, using SFML 2.5.1

Only optimized for 1080p Windows systems.

`ctrl + backspace` deletes the whole entry.

`return` inputs a guess, or restarts the game if it has ended.

`escape` exits the game.

The keyboard isn't clickable: it's just there to track letters.

This was really my first complete game. Architecturally, it's not quite as much of a mess as some of the prototypes I've made, but it was very much a learning project.

Word list is a lightly edited version of Alan Beale's 12Dicts American 2of12inf list, version 6.0.2:  
http://wordlist.aspell.net/12dicts/  
Edits include removing archaic/obsolete words, slurs, a couple words I plain don't like, and a few inexplicable british english formes. Some words were added.

RoundedRectangleShape class was written by Rémi Bèges, from the SFML wiki:  
https://github.com/SFML/SFML/wiki/Source:-Draw-Rounded-Rectangle

Font is Iosevka:  
https://github.com/be5invis/iosevka

#include "primordial.h"

void randomSeed(){
    srand(time(NULL));
}

int randomInteger(int floor, int ceil){
    ++ ceil -= floor;
    int random = rand()%ceil + floor;
    return random;
}

std::string makeUppercase(std::string str){
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

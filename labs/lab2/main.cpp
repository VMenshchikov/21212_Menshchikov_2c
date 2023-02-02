#include "BlackJack/BlackJack.hpp"
#include "BlackJack/BlackJackSettings.hpp"



int main(int argc, char** argv){
    TConfig A = TConfig(argc, argv);
    TBlackJack Game(A);
    Game.Game(Game.GetCountPart());
    return 0;
} 

#include "BlackJack/BlackJack.hpp"
#include "BlackJack/BlackJackSettings.hpp"

int main(){
    TConfig A = TConfig(0, 10, 100, {"Player", "Player"}, "detailed", 3, 3);
    TBlackJack Game(A);
    Game.Game(Game.GetCountPart());
    return 0;
} 

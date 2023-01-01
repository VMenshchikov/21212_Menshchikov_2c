#include "BlackJack/BlackJack.hpp"
#include "BlackJack/BlackJackSettings.hpp"



int main(int argc, char** argv){
    //TConfig A = TConfig(0, 1, 1000, {"OneHit", "TwoHit", "SplitAndHit", "DoubleDown", "CopyDiler"}, "tournament", 8, 2000);
    TConfig A = TConfig(argc, argv);
    //std::cout << "\n" << A.bank <<"\n" <<A.bet << "\n" <<A.countDeck <<"\n" <<A.countPart << "\n" <<A.modeGame << "\n" << A.players[0] << "\n" << A.players[1] << std::endl;
    TBlackJack Game(A);
    Game.Game(Game.GetCountPart());
    return 0;
} 

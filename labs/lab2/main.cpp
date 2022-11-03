#include "BlackJack.hpp"
#include "BlackJackSettings.hpp"

int main(){
    TConfig A = TConfig(10, 100, {"Diler", "Diler"}, 3);
    TBlackJack Game = TBlackJack(A);
    return 0;
}
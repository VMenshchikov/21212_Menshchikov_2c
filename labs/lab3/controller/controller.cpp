#include "../../lab2/BlackJack/EnumAction.hpp"
#include "../../lab2/BlackJack/BlackJack.hpp"
#include "controller.hpp"
#include "playerUI.hpp"
#include <vector>


static void TController::startGame(size_t bet, size_t bank, size_t parts){
    game(TConfig(0, bet, bank, {"PlayerUI"}, "tournament", 8, parts));
    game.Game(game.GetCountPart);
}

static int TController::getDilerCard(){
    return game.DilerCard;
}

static std::vector<int> TController::getPlayerCards(){
    return game
}
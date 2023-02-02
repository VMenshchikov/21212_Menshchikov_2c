#include "../game/BlackJack/EnumAction.hpp"
#include "../game/BlackJack/BlackJack.hpp"
#include "controller.hpp"
#include "playerUI.hpp"
#include <vector>

TController::TController(StartWindow* w) : w(w){};

TController::~TController() {
}

void TController::startGame(size_t bet, size_t bank, size_t parts) {
    game = std::make_unique<TBlackJack>(TConfig(*this, 0, bet, bank,
                {"PlayerUI"}, "UI", 8, parts));
    QObject::connect(
           w->getGameWindow(),
           SIGNAL(endGame()),
           this,
           SLOT(endGame()));
    QObject::connect(
           game,
           SIGNAL(newCard(int, std::string, bool, bool, int)),
           w->getGameWindow(),
           SLOT(newCard(int,std::string, bool, bool, int)));
    QObject::connect(
           w->getGameWindow(),
           SIGNAL(sendAction(std::string)),
           game,
           SLOT(setUIAct(std::string)));
    QObject::connect(
           game,
           SIGNAL(newBank(int,int)),
           w->getGameWindow(),
           SLOT(newBank(int,int)));
    QObject::connect(
           game,
           SIGNAL(endPart()),
           w->getGameWindow(),
           SLOT(endPart()));
    QObject::connect(
           game,
           SIGNAL(dilerCard(int)),
           w->getGameWindow(),
           SLOT(dilerCard(int)));
    QObject::connect(
           game,
           SIGNAL(finalResult(int,int)),
           w->getGameWindow(),
           SLOT(finalResult(int,int)));
    QObject::connect(
           w->getGameWindow(),
           SIGNAL(newRevPause(int)),
           game,
           SLOT(newRevPause(int)));
    game->Game(game->GetCountPart());

};

int TController::getDilerCard() { return game->GetDilerCard(); }

void TController::convertToActions(THand hand) {
    char actions = 0b00011111; //Hit Stand DD Surrender Split
    if (hand.MyCards.capacity() > 2) {
        actions &= 0b11100011; //-DD&&Su&&Sp
    }
    if (hand.MyCards[0] != hand.MyCards[1]) {
        actions &= 0b11101111; //-Sp
    }
    if (hand.NumStep > 1) {
        actions &= 0b11100111; //-Sp&&Su
    }
    if (hand.MySum < hand.MyBet) {
        actions &= 0b11101011; //-Sp&DD
    }

    emit uiActions(actions);
}

void TController::endGame() {
    if (game != nullptr) { delete game; };
}

void TController::connect(){
    QObject::connect(
          w->getGameWindow(),
          SIGNAL(startGame(size_t, size_t, size_t)),
          this,
          SLOT(startGame(size_t, size_t, size_t)));
    QObject::connect(
           this,
           SIGNAL(uiActions(char)),
           w->getGameWindow(),
           SLOT(decision(char)));
}


void TController::connectUI(TStrategy& s){
    QObject::connect(
           &s,
           SIGNAL(needMove(THand, const TBlackJack*)),
           this,
           SLOT(convertToActions(THand)));
}

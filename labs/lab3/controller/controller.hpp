#pragma once

#include "../../lab2/BlackJack/BlackJack.hpp"

class TController {
  public:
    static void startGame(size_t bet, size_t bank, size_t parts);
    static int getDilerCard();
    static std::vector<int> getPlayerCards();


  private:
    static TBlackJack game;
}
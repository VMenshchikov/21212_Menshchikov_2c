#pragma once

#include "BlackJackSettings.hpp"
#include "Player.hpp"

#include <iostream>
#include <list>
#include <string>
#include <vector>

class TPlayer;

class TBlackJack {
  public:
    TBlackJack(TConfig);
    void Game() {
        StartGame();
        Play();
        Results();
    }

    const int GetCard(bool visible);
    const int GetSizeDeck() const;
    const std::vector<int> GetVisibleCards() const;

  private:
    std::vector<int> AllVisibleCards = {};
    int CurrentSizeDeck;
    std::list<int> CurrentDeck;
    std::vector<TPlayer> Players;
    TBlackJackSettings Settings;

    void CreateDeck(int ModeDeck);

    void StartGame();
    void Play();
    void Results();
};

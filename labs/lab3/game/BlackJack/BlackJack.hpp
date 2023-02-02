#pragma once

#include "BlackJackSettings.hpp"
#include "Player.hpp"

#include <list>
#include <string>
#include <vector>

#include <QObject>

class TPlayer;

class TBlackJack : public QObject{
    Q_OBJECT
  public:
    TBlackJack(TConfig config);
    virtual ~TBlackJack(){};

    int GetCard(bool visible, std::string name, bool pos, int count);
    int GetDilerCard() const { return DilerCard; }
    int GetSizeDeck() const { return CurrentSizeDeck; }
    int GetBet() const { return Settings.bet; }
    const std::string &GetModeGame() const { return Settings.modeGame; }
    const std::vector<int> &GetVisibleCards() const { return AllVisibleCards; }
    int GetCountPart() { return Settings.countPart; }

    void Game(size_t count, int aftherUI = 0);

  public slots:
    void setUIAct(std::string act);
    void newRevPause(int t);

  signals:
    void newCard(int, std::string, bool, bool, int);
    void uiPlay(TBlackJack &table, TPlayer &player);
    void newBank(int,int);
    void endPart();
    void dilerCard(int);
    void finalResult(int, int);

  private:

    std::vector<int> AllVisibleCards = {};
    int CurrentSizeDeck;
    int CurrentCountPart;
    std::list<int> CurrentDeck;
    std::vector<TPlayer> Players;
    int indLastP = 0;
    int DilerCard;
    const TConfig Settings;
    int revPause = 0;

    void CreateDeck();
    void ReplenishmentDeck() { CreateDeck(); };

    void beforeGame();
    void aftherGame();

    void StartGame();
    int Play();
    void Results();
    void PrintResult();
};

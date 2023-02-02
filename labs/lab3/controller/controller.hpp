#pragma once

#include <QObject>

#include "../game/BlackJack/BlackJack.hpp"
#include "../interface/BlackJack/startwindow.h"

class TController : public QObject{
    Q_OBJECT
  public:
    TController(StartWindow* w);
    virtual ~TController();

    int getDilerCard();

    void connect();
    void connectUI(TStrategy& s);

  signals:
    void uiActions(char);

  public slots:
    void startGame(size_t bet, size_t bank, size_t parts);
    void convertToActions(THand hand);
    void endGame();



  private:
    std::unique_ptr<TBlackJack> game;
    StartWindow* w;

};

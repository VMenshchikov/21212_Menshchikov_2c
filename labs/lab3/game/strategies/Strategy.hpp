#pragma once

#include <vector>
#include <QObject>

#include "../BlackJack/BlackJack.hpp"
#include "../BlackJack/PlayerHand.hpp"
#include "../BlackJack/EnumAction.hpp"


class TBlackJack;


class TStrategy : public QObject {
  public:
    virtual EAction SelectAction(const THand& hand, const TBlackJack& table) = 0;
    virtual ~TStrategy() = default;
};

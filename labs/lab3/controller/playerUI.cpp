#include "playerUI.hpp"
#include "../game/BlackJack/EnumAction.hpp"
#include <QThread>

// реализация
EAction TPlayerUI::SelectAction(const THand &hand, const TBlackJack &table) {

    emit needMove(hand, &table);

    return EAction::eNull;
}



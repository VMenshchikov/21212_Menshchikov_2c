#include "DilerStrategy.hpp"
#include "../../BlackJack/EnumAction.hpp"

// реализация
EAction TDiler::SelectAction(const THand &hand, const TBlackJack &table) {
    if (hand.MySum < 17) {
        return EAction::eHit;
    };
    return EAction::eStand;
};

#include "CopyDilerStrategy.hpp"
#include "../../BlackJack/EnumAction.hpp"

// реализация
EAction TCopyDiler::SelectAction(const THand &hand, const TBlackJack &table) {
    if (hand.MySum < 18) {
        return EAction::eHit;
    };
    return EAction::eStand;
};

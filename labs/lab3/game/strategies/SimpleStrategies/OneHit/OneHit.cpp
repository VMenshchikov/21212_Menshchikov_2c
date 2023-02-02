#include "OneHit.hpp"
#include "../../../BlackJack/EnumAction.hpp"

// реализация
    EAction TOneHit::SelectAction(const THand &hand, const TBlackJack &table) {
        if (hand.NumStep == 1) {
            return EAction::eHit;
        };
        return EAction::eStand;
    }

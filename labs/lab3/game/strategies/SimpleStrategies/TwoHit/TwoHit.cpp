#include "TwoHit.hpp"
#include "../../../BlackJack/EnumAction.hpp"

// реализация
    EAction TTwoHit::SelectAction(const THand &hand, const TBlackJack &table) {
        if (hand.NumStep  < 3) {
            return EAction::eHit;
        };
        return EAction::eStand;
    }

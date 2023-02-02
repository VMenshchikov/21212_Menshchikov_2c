#include "SplitAndHit.hpp"
#include "../../../BlackJack/EnumAction.hpp"

// реализация
    EAction TSplitAndHit::SelectAction(const THand &hand, const TBlackJack &table) {
        if (hand.NumStep == 1 && hand.MyCards[0] == hand.MyCards[1]) {
            return EAction::eSplit;
        };
        if (hand.NumStep == 2) {
            return EAction::eHit;
        };
        return EAction::eStand;
    }

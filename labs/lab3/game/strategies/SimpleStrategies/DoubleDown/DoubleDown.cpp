#include "DoubleDown.hpp"
#include "../../../BlackJack/EnumAction.hpp"

// реализация
    EAction TDoubleDown::SelectAction(const THand &hand, const TBlackJack &table) {
        if (hand.NumStep == 1) {
            return EAction::eDoubleDoun;
        };
        return EAction::eStand;
    }

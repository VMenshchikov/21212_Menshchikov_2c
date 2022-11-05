#include "DilerStrategy.hpp"
#include "../../BlackJack/EnumAction.hpp"

// реализация
EAction TDiler::SelectAction(const THand &hand) { return EAction::eStand; };

namespace {
TStrategy *Create() { return new TDiler; }
const bool reg =
    TStrategyFactory::GetInstance()->RegisterStrategy("Diler", Create);
} 
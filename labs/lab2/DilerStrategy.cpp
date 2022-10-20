#include "DilerStrategy.hpp"

//реализация

namespace {
TStrategy *Create() { return new TDiler; }
const bool reg =
    TStrategyFactory::GetInstance()->RegisterStrategy("Diler", Create);
} 
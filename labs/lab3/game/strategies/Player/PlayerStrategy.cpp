#include "PlayerStrategy.hpp"
#include "../../BlackJack/EnumAction.hpp"
#include <iostream>

// реализация
EAction TPlayerS::SelectAction(const THand &hand, const TBlackJack &table) {

    std::cout << "-------------------------------" << std::endl
              << "Current visible cards: ";
    ;
    auto cards = table.GetVisibleCards();
    for (auto i : cards) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "Current your cards: ";
    
    for (auto i = hand.MyCards.begin(); i != hand.MyCards.end(); i++) {
        std::cout << *i << " ";
    }

    std::cout << std::endl
              << "Diller card: " << table.GetDilerCard() << std::endl;

    while (true) {
        std::cout << "-------------------------------" << std::endl;
        std::cout << "Your move, choose an action(H/St/DD/Sp/Su):";
        std::string move;
        std::cin >> move;

        if (move == "H") {
            return EAction::eHit;
        }
        if (move == "St") {
            return EAction::eStand;
        }
        if (move == "DD") {
            return EAction::eDoubleDoun;
        }
        if (move == "Sp") {
            return EAction::eSplit;
        }
        if (move == "Su") {
            return EAction::eSurrender;
        }
        std::cout << "invalid action, repeat" << std::endl;
    }
}

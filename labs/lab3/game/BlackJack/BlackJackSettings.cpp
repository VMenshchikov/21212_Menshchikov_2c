#include "BlackJackSettings.hpp"
#include "../Factory/Factory.hpp"
#include <boost/program_options.hpp>

TConfig::TConfig(TController& contr, size_t srandPar, size_t bet, size_t startBank,
                 std::vector<std::string> &&playersStr, std::string modeGame,
                 size_t countDeck, size_t countPart)
    : bet(bet), startBank(startBank), playersStr(playersStr), countDeck(countDeck),
      countPart(countPart), modeGame(modeGame), contr(contr) {

    if (bet > startBank || countDeck > 16 || startBank > 1000000 || countPart > 10000000)
        throw(std::invalid_argument("bet/bank/deck/part"));
    if (!(modeGame == "tournament" || modeGame == "detailed" || modeGame == "UI"))
        throw(std::invalid_argument("modeGame"));
    if (playersStr.size() < 1)
        throw(std::invalid_argument(" 0 players"));

    this->playersStr.push_back("Diler");
    srand(srandPar == 0 ? time(0) : srandPar);
};

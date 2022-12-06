#include "BlackJackSettings.hpp"
#include "../Factory/Factory.hpp"
#include <boost/program_options.hpp>

TConfig::TConfig(size_t srandPar, size_t bet, size_t bank,
                 std::vector<std::string>&& players, std::string modeGame,
                 size_t countDeck, size_t countPart)
    : bet(bet), bank(bank), players(players), countDeck(countDeck),
      modeGame(modeGame), countPart(countPart) {
    this->players.push_back("Diler");
    srand(srandPar == 0 ? time(0) : srandPar);
};

TConfig::TConfig(int argc, char **argv){
    // program_options parser
};

TBlackJackSettings::TBlackJackSettings(TConfig config)
    : ModeGame(config.modeGame), Bet(config.bet), StartBank(config.bank),
      ModeDeck(config.countDeck), PlayersStr(config.players),
      CountPart(config.countPart){};

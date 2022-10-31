#include "BlackJackSettings.hpp"
#include "Factory.hpp"
#include "boost/program_options.hpp"

TConfig::TConfig(size_t bet, size_t bank, std::vector<std::string> players,
                 std::string modeGame, size_t countDeck = 0)
    : bet(bet), bank(bank), players(players), countDeck(countDeck),
      modeGame(modeGame){};

TConfig::TConfig(size_t bet, size_t bank, std::vector<std::string> players,
                 size_t countDeck = 0)
    : bet(bet), bank(bank), players(players), countDeck(countDeck) {
    modeGame = players.size() == 2 ? "detailed" : "fast";
};

TConfig::TConfig(int argc, char **argv){
    // program_options parser
};

TBlackJackSettings::TBlackJackSettings(TConfig config)
    : ModeGame(config.modeGame), Bet(config.bet), StartBank(config.bank),
      ModeDeck(config.countDeck), PlayersStr(config.players){};
const std::string TBlackJackSettings::GetModeGame() const {
    return ModeGame;
}
const std::vector<std::string> TBlackJackSettings::GetPlayers() const {
    return PlayersStr;
}
const int TBlackJackSettings::GetModeDeck() const {
    return ModeDeck;
}
#include "BlackJackSettings.hpp"
#include "Factory.hpp"

TBlackJackSettings::TBlackJackSettings(size_t bet, size_t countDeck,
                                       std::string modeGame,
                                       std::vector<std::string> players)
    : Bet(bet), ModeDeck(countDeck), ModeGame(modeGame), PlayersStr(players) {
    for (auto s : players) {
        Players.push_back(TStrategyFactory::GetInstance()->GetObject(s));
    }
}
TBlackJackSettings::TBlackJackSettings(size_t bet, size_t countDeck,
                                       std::vector<std::string> players)
    : Bet(bet), ModeDeck(countDeck), PlayersStr(players) {
    for (auto s : players) {
        Players.push_back(TStrategyFactory::GetInstance()->GetObject(s));
    }
    ModeGame = players.size() == 2 ? "detailed" : "tournament";
};

const int TBlackJackSettings::GetModeDeck() const { return ModeDeck; }
const std::string TBlackJackSettings::GetModeGame() const { return ModeGame; }
const std::vector<std::string> TBlackJackSettings::GetPlayers() const {
    return PlayersStr;
}
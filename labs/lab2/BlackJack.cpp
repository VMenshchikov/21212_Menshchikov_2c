#include "BlackJack.hpp"
#include "Factory.hpp"
//{ TabWidth: 4, IndentWidth: 4, ColumnLimit: 80 }

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
// qq

const int TBlackJackSettings::GetModeDeck() const { return ModeDeck; }
const std::string TBlackJackSettings::GetModeGame() const { return ModeGame; }
const std::vector<std::string> TBlackJackSettings::GetPlayers() const {
    return PlayersStr;
}

TBlackJack::TBlackJack(int CountArg, char *args){
    //--mode=[detailed|fast|tournament]             //optional
    //--configs=<dirname>                           //??
    //--bank=*start_bank_size*                      //always
    //--players=*count_players* name1 name2 name3   //always



};
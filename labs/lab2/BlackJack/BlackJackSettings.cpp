#include "BlackJackSettings.hpp"
#include "../Factory/Factory.hpp"
#include <boost/program_options.hpp>

TConfig::TConfig(size_t srandPar, size_t bet, size_t bank,
                 std::vector<std::string> &&players, std::string modeGame,
                 size_t countDeck, size_t countPart)
    : bet(bet), bank(bank), players(players), countDeck(countDeck),
      modeGame(modeGame), countPart(countPart) {
    this->players.push_back("Diler");
    srand(srandPar == 0 ? time(0) : srandPar);
};

TConfig::TConfig(int argc, char **argv) { //смесь хабра и чего-та английского
    // program_options parser
    using namespace boost::program_options;
    options_description desc("General options");
    std::string task_type;
    desc.add_options()
        ("Help,h", "Show help")
        ("Mode,M", value<std::string>(),"ModeGame(detailed/tournament)")
        ("CountPart,C", value<size_t>(), "Count parts in game")
        ("Player,P", value<std::vector<std::string>>(),"Select strategy")
        ("CountDeck,D", value<size_t>(), "Select count decks")
        ("Bank,B", value<size_t>(), "Money")
        ("Bet,b", value<size_t>(), "Size bet");

    variables_map vm;
    parsed_options parsed = command_line_parser(argc, argv)
                                .options(desc)
                                .allow_unregistered()
                                .run();
    store(parsed, vm);
    notify(vm);

    if (vm.count("Help")) {
        std::cout << desc << std::endl;
        std::cout << "Min args: Player, Bank and Bet" << std::endl;
    } else {
        if (vm.count("Bet") && vm.count("Bank") && vm.count("Player")) {
            bet = vm["Bet"].as<size_t>();
            bank = vm["Bank"].as<size_t>();
            players = vm["Player"].as<std::vector<std::string>>();
            if(!vm.count("Mode")){
                modeGame = "detailed";
            } else {
                modeGame = vm["Mode"].as<std::string>();
            }
            if(vm.count("CountDeck")) {
                countDeck = vm["CountDeck"].as<size_t>();
            } else {
                if (modeGame == "detailed") {
                    countDeck = 1;
                } else {
                    countDeck = 5;
                }
            }
            if(vm.count("CountPart")) {
                countPart = vm["CountPart"].as<size_t>();
            } else {
                if (modeGame == "detailed") {
                    countPart = 10;
                } else {
                    countPart = 100;
                }
            }

        } else {
            std::cout << "Error, min args: Bet, Bank, Player" << std::endl;
            throw(std::invalid_argument("bad argv"));
        }
    }
    std::srand(time(0));
};

TBlackJackSettings::TBlackJackSettings(TConfig config)
    : ModeGame(config.modeGame), Bet(config.bet), StartBank(config.bank),
      ModeDeck(config.countDeck), PlayersStr(config.players),
      CountPart(config.countPart){};

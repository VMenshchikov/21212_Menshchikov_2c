#include "BlackJackSettings.hpp"
#include "../Factory/Factory.hpp"
#include <boost/program_options.hpp>

TConfig::TConfig(size_t srandPar, size_t bet, size_t startBank,
                 std::vector<std::string> &&playersStr, std::string modeGame,
                 size_t countDeck, size_t countPart)
    : bet(bet), startBank(startBank), playersStr(playersStr), countDeck(countDeck),
      modeGame(modeGame), countPart(countPart) {

    if (bet > startBank || countDeck > 16 || startBank > 1000000 || countPart > 10000000)
        throw(std::invalid_argument("bet/bank/deck/part"));
    if (!(modeGame == "tournament" || modeGame == "detailed"))
        throw(std::invalid_argument("modeGame"));
    if (playersStr.size() < 1)
        throw(std::invalid_argument(" 0 players"));

    this->playersStr.push_back("Diler");
    srand(srandPar == 0 ? time(0) : srandPar);
};

TConfig::TConfig(int argc, char **argv) { // смесь хабра и чего-тo английского
    // program_options parser
    using namespace boost::program_options;
    options_description desc("General options");
    std::string task_type;
    desc.add_options()
        ("Help,h", "Show help")
        ("Mode,M", value<std::string>(),"ModeGame(detailed/tournament)")
        ("CountPart,P", value<size_t>(), "Count parts in game")
        ("Player,P", value<std::vector<std::string>>(), "Select strategy")
        ("CountDeck,D", value<size_t>(), "Select count decks")
        ("Bank,B", value<size_t>(), "Money")
        ("Bet,b", value<size_t>(),"Size bet")
        ("Time,t", value<int>(),"Seed for rand()");

    variables_map vm;
    parsed_options parsed = command_line_parser(argc, argv)
                                .options(desc)
                                .allow_unregistered()
                                .run();
    store(parsed, vm);
    notify(vm);

    if (vm.count("Help")) {
        std::cout << desc << std::endl;
        std::cout << "Min args: Player, startBank and Bet" << std::endl;
        exit(0);
    } else {
        if (vm.count("Bet") && vm.count("startBank") && vm.count("Player")) {
            bet = vm["Bet"].as<size_t>();
            startBank = vm["startBank"].as<size_t>();
            playersStr = vm["Player"].as<std::vector<std::string>>();
            if (!vm.count("Mode")) {
                modeGame = "detailed";
            } else {
                modeGame = vm["Mode"].as<std::string>();
            }
            if (vm.count("CountDeck")) {
                countDeck = vm["CountDeck"].as<size_t>();
            } else {
                if (modeGame == "detailed") {
                    countDeck = 1;
                } else {
                    countDeck = 5;
                }
            }
            if (vm.count("CountPart")) {
                countPart = vm["CountPart"].as<size_t>();
            } else {
                if (modeGame == "detailed") {
                    countPart = 10;
                } else {
                    countPart = 100;
                }
            }

        } else {
            std::cout << "Error, min args: Bet, startBank, Player" << std::endl;
            throw(std::invalid_argument("bad argv"));
        }
    }
    if (vm.count("Time")) {
        std::srand(vm["Time"].as<int>());
    } else {
        std::srand(time(0));
    }
    // add Diller
    playersStr.push_back("Diler");
};

cmake_minimum_required(VERSION 3.5)

project(BlackJack LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.



find_package(Qt5 COMPONENTS Widgets UiTools Test REQUIRED)


  add_executable(BlackJack
    startwindow.cpp
    startwindow.h
    startwindow.ui
    ../resourses/leaders.txt
    gamewindow.ui
    gamewindow.h
    gamewindow.cpp
    Factory/Factory.hpp

    ../../controller/controller.cpp
    ../../controller/controller.hpp
    ../../controller/playerUI.hpp
    ../../controller/playerUI.cpp


    ../../game/strategies/Strategy.hpp
    ../../game/strategies/Diler/DilerStrategy.cpp
    ../../game/strategies/Diler/DilerStrategy.hpp
#   ../../game/strategies/CopyDil/CopyDilerStrategy.cpp
#   ../../game/strategies/CopyDil/CopyDilerStrategy.hpp
#   ../../game/strategies/Player/PlayerStrategy.hpp
#   ../../game/strategies/Player/PlayerStrategy.cpp

#    ../../game/strategies/SimpleStrategies/OneHit/OneHit.cpp
#    ../../game/strategies/SimpleStrategies/OneHit/OneHit.hpp
#    ../../game/strategies/SimpleStrategies/TwoHit/TwoHit.cpp
#    ../../game/strategies/SimpleStrategies/TwoHit/TwoHit.hpp
#    ../../game/strategies/SimpleStrategies/SplitAndHit/SplitAndHit.cpp
#    ../../game/strategies/SimpleStrategies/SplitAndHit/SplitAndHit.hpp
#    ../../game/strategies/SimpleStrategies/DoubleDown/DoubleDown.cpp
#    ../../game/strategies/SimpleStrategies/DoubleDown/DoubleDown.hpp

    ../../game/BlackJack/BlackJack.cpp
    ../../game/BlackJack/BlackJack.hpp
    ../../game/BlackJack/BlackJackSettings.cpp
    ../../game/BlackJack/BlackJackSettings.hpp
    ../../game/BlackJack/EnumAction.hpp
    ../../game/BlackJack/Player.cpp
    ../../game/BlackJack/Player.hpp
    ../../game/BlackJack/PlayerHand.hpp
    ../../game/BlackJack/Printer.hpp

    ../../game.cpp
    )


target_link_libraries(BlackJack PRIVATE Qt5::Widgets Qt5::Test)

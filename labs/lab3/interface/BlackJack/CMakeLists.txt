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

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets UiTools REQUIRED)
#find_package(Qt6 REQUIRED COMPONENTS UiTools)

if(ANDROID)
  add_library(BlackJack SHARED
    main.cpp
    startwindow.cpp
    startwindow.h
    startwindow.ui
    statistic.ui
    leaders.txt
    gamewindow.cpp
    gamewindow.h
    gamewindow.ui
    Factory/cardsFactory.cpp
    Factory/Factory.hpp

  )
else()
  add_executable(BlackJack
    main.cpp
    startwindow.cpp
    startwindow.h
    startwindow.ui
    leaders.txt
    gamewindow.ui
    gamewindow.h
    gamewindow.cpp
    Factory/cardsFactory.cpp
    Factory/Factory.hpp
  )
endif()

#target_link_libraries(BlackJack PRIVATE Qt6::UiTools)

target_link_libraries(BlackJack PRIVATE Qt5::Widgets)

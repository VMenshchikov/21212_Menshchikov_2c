#pragma once

#include "PlayerHand.hpp"
#include <iostream>
// #include <Q

class Printer {
  public:
    // Player.cpp
    static void PrintHit(const THand &hand, bool flag) {
        std::cout << "You took the card(" << hand.MyCards.back()
                  << "). Current score: " << hand.MySum << "." << std::endl;
        if (flag) {
            std::cout << "Game continues" << std::endl;
        } else {
            std::cout << "You lost" << std::endl;
        }
    }
    static void PrintStand(const THand &hand) {
        std::cout << "You have finished your turn. Your score: " << hand.MySum
                  << std::endl;
    }
    static void PrintDoubleDown(const THand &hand, bool flag) {

        std::cout << "DoubleDown.\nYou took the card(" << hand.MyCards.back()
                  << "). Current score: " << hand.MySum << ". "
                  << "Your current bet: " << hand.MyBet << std::endl;
        std::cout << "Current score: " << hand.MySum << std::endl;
        if (flag) {
            std::cout << "Game continues." << std::endl;
        } else {
            std::cout << "You lost." << std::endl;
        }
    }
    static void PrintSplit(int sum0, int sum1) {
        std::cout << "You split your hand." << std::endl
                  << "First hand score: " << sum0 << "\t||\t"
                  << "Second hand score: " << sum1 << std::endl;
    }
    static void PrintSurrender(int MyBank) {
        std::cout << "You gave up. Half of the bet returned. Your bank: "
                  << MyBank << std::endl;
    }
    static void PrintPlaingHand(int numHand) {
        std::cout << "\nPlaying hand " << numHand << "." << std::endl;
    }

    // BlacjJack.cpp
    static void PrintSeparation() {
        std::cout << "*************************************" << std::endl;
    }
    static void PrintPlayingPlayer(size_t num,
                                   const std::vector<std::string> &player) {
        std::cout << "*Playing: " << player[num] << "(" << num + 1 << ")"
                  << std::endl;
    }
    static void PrintSeparationPlayers() {
        std::cout << "-------------------------" << std::endl;
    }

    static void PrintDillerCards(std::vector<int> allDellerCards) {
        std::cout << "Diller cards: ";
        for (auto i : allDellerCards) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    static void PrintPlayerResult(std::string name, size_t cash, int number) {
        std::cout << number << ") Name: " << name << " | Bank: " << cash
                  << std::endl;
    }

    static void PrintWinner(std::vector<std::string> winners){
        std::cout << "\nWinner(s): ";
        for (auto i: winners){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};


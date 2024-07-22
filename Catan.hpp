#pragma once
#ifndef CATAN_HPP
#define CATAN_HPP
#include <iostream>
#include <vector>
#include <map>
#include "Player.hpp"
#include "Board.hpp"

using namespace std;

namespace ariel
{
    class Player;
    class Board;

    class Catan
    {
    private:
        Board *board;
        vector<Player *> players;
        Player *current;
        Cards *cards;

    public:
        Catan(Player &p1, Player &p2, Player &p3);
        void setCards();
        void setBoard();
        ~Catan();
        Board *getBoard();
        Cards *getCards();
        vector<Player *> getPlayers();
        Player *getCurrent();
        void setCurrent(Player *p);
        void chooseStartingPlayer();
        void turnSwitch();
        bool victory(Player *player);
        void printVictory(Player *player);
        void rollDice(Player *player);
        void rollDiceResourceAdd(int number);
        void sevenDice();
    };
}

#endif
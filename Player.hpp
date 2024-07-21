#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "Cards.hpp"
#include "Catan.hpp"
#include "Board.hpp"

using namespace std;

namespace ariel
{

    class Board;
    class Catan;

    class Player
    {
    private:
        string name;
        int points;
        map<string, int> resources;
        map<string, int> cards;

    public:
        Player();
        Player(string name);
        void initCards();
        void initResources();
        int getPoints();
        void addPoints(int num);
        void printPoints();
        void printResourceMap();
        void printCardMap();
        string getName();
        map<string, int> getCards();
        void addCard(string card, int amount);
        void reduceCard(string card, int amount);
        map<string, int> getResources();
        void reduceResource(string resource, int num);
        void addResource(string resource, int num);
        int totalResourceCount();
        void placeFirstSettlemnts(size_t vertexNum1, size_t vertexNum2, Board *b);
        void placeFirstRoads(size_t edgeNum1, size_t edgeNum2, Board *b);
        void addBiggestArmyCard(Cards &cardsPack);
        void buyCard(Cards &cardsPack);
        void useVictoryPointCard(Catan *catan);
        void useYearOfPlentyCard(string card1, string card2, Catan *catan);
        void useMonopolyCard(vector<Player *> players, string Resource, Catan *catan);
        void useBuildRoadsCard(size_t VertexNum1, size_t VertexNum2, Board *b, Catan *catan);
        bool checkEdgeNearEdge(size_t edgeNum, Board *b);
        void placeRoad(size_t edgeNum, Board *b);
        void placeTwoRoadsBuildCard(size_t edgeNum1, size_t edgeNum2, Board *b);
        void placeSettlement(size_t vertexNum, Board *b);
        void placeCity(size_t vertexNum, Board *b);
        bool checkDistance(size_t vertexNum, Board *b);
        void rollDice(Catan *c);
        void returnHalf();
        void tradeResources(Catan *catan, Player *other, string thisResource, int thisAmount, string otherResource, int otherAmount);
        void tradeCards(Catan *catan, Player *other, string thisCard, int thisAmount, string otherCard, int otherAmount);
    };
};

#endif

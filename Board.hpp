#pragma once
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Tile.hpp"
#ifndef BOARD_HPP
#define BOARD_HPP
#include "Player.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

namespace ariel
{

    class Vertex;
    class Edge;
    class Player;
    class Tile;

    class Board
    {
    private:
        vector<Vertex *> vertices;
        vector<Edge *> edges;
        vector<Tile *> tiles;

    public:
        Board();
        void initVertices();
        void initEdges();
        void initTiles();
        vector<Vertex *> getVertices();
        vector<Edge *> getEdges();
        vector<Tile *> getTiles();
        bool isAvailableVertex(size_t v);
        void setPlayerAtVertex(size_t v, Player *p);
        void setTypeAtVertex(size_t v, string s);
        bool isAvailableEdge(size_t e);
        void setPlayerAtEdge(size_t e, Player *p);
    };

};

#endif
#pragma once
#ifndef TILE_HPP
#define TILE_HPP
#include <vector>
using namespace std;
#include "Vertex.hpp"

namespace ariel
{

    class Vertex;
    class Edge;

    class Tile
    {

        static size_t idCountTile;

    private:
        string type;
        string resource;
        vector<Vertex *> vertices;
        size_t number;
        size_t index;

    public:
        Tile(string type, string resource, vector<Vertex *> vertices, size_t num);
        ~Tile();
        string getType();
        string getResource();
        vector<Vertex *> getVertices();
        size_t getNum();
        size_t getIndex();
        static void resetIdCount();
    };

};

#endif
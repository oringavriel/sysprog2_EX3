#pragma once
#ifndef EDGE_HPP
#define EDGE_HPP

#include "Vertex.hpp"

namespace ariel
{

    class Vertex;
    class Player;

    class Edge
    {
        static size_t idCountEdge;

    private:
        Vertex *v1;
        Vertex *v2;
        Player *p = nullptr;
        size_t index;

    public:
        Edge(Vertex *v1, Vertex *v2);
        Vertex *getV1();
        Vertex *getV2();
        Player *getPlayer();
        void setPlayer(Player *p);
        size_t getIndex();
        static void resetIdCount();
    };
};

#endif
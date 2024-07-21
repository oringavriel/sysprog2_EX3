#pragma once
#include <stdexcept>
#include <string>
#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Player.hpp"
using namespace std;

namespace ariel
{

    class Player;

    class Vertex
    {
        static size_t idCountVertex;

    private:
        string type;
        Player *p = nullptr;
        size_t index;

    public:
        Vertex();
        Player *getPlayer();
        void setPlayer(Player *p);
        string getType();
        void setType(string type);
        size_t getIndex();
        static void resetIdCount();
    };
};

#endif
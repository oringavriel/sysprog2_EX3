#include "Board.hpp"
#include "Tile.hpp"
#include "Player.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;
using namespace ariel;

void Board::initVertices()
{
    for (size_t i = 0; i < 54; ++i)
    { // 0-54 : 54 vertices
        vertices.push_back(new Vertex());
    }
}

void Board::initEdges()
{                                                          // 0-71: 72 edges
    edges.push_back(new Edge(vertices[3], vertices[0]));   // 0
    edges.push_back(new Edge(vertices[0], vertices[4]));   // 1
    edges.push_back(new Edge(vertices[4], vertices[1]));   // 2
    edges.push_back(new Edge(vertices[1], vertices[5]));   // 3
    edges.push_back(new Edge(vertices[5], vertices[2]));   // 4
    edges.push_back(new Edge(vertices[2], vertices[6]));   // 5
    edges.push_back(new Edge(vertices[7], vertices[3]));   // 6
    edges.push_back(new Edge(vertices[4], vertices[8]));   // 7
    edges.push_back(new Edge(vertices[5], vertices[9]));   // 8
    edges.push_back(new Edge(vertices[6], vertices[10]));  // 9
    edges.push_back(new Edge(vertices[7], vertices[11]));  // 10
    edges.push_back(new Edge(vertices[12], vertices[7]));  // 11
    edges.push_back(new Edge(vertices[8], vertices[12]));  // 12
    edges.push_back(new Edge(vertices[13], vertices[8]));  // 13
    edges.push_back(new Edge(vertices[9], vertices[13]));  // 14
    edges.push_back(new Edge(vertices[14], vertices[9]));  // 15
    edges.push_back(new Edge(vertices[10], vertices[14])); // 16
    edges.push_back(new Edge(vertices[15], vertices[10])); // 17
    edges.push_back(new Edge(vertices[11], vertices[16])); // 18
    edges.push_back(new Edge(vertices[12], vertices[17])); // 19
    edges.push_back(new Edge(vertices[13], vertices[18])); // 20
    edges.push_back(new Edge(vertices[14], vertices[19])); // 21
    edges.push_back(new Edge(vertices[20], vertices[15])); // 22
    edges.push_back(new Edge(vertices[16], vertices[21])); // 23
    edges.push_back(new Edge(vertices[16], vertices[22])); // 24
    edges.push_back(new Edge(vertices[22], vertices[17])); // 25
    edges.push_back(new Edge(vertices[17], vertices[23])); // 26
    edges.push_back(new Edge(vertices[23], vertices[18])); // 27
    edges.push_back(new Edge(vertices[18], vertices[24])); // 28
    edges.push_back(new Edge(vertices[24], vertices[19])); // 29
    edges.push_back(new Edge(vertices[19], vertices[25])); // 30
    edges.push_back(new Edge(vertices[25], vertices[20])); // 31
    edges.push_back(new Edge(vertices[20], vertices[26])); // 32
    edges.push_back(new Edge(vertices[27], vertices[21])); // 33
    edges.push_back(new Edge(vertices[28], vertices[22])); // 34
    edges.push_back(new Edge(vertices[29], vertices[23])); // 35
    edges.push_back(new Edge(vertices[30], vertices[24])); // 36
    edges.push_back(new Edge(vertices[31], vertices[25])); // 37
    edges.push_back(new Edge(vertices[26], vertices[32])); // 38
    edges.push_back(new Edge(vertices[33], vertices[27])); // 39
    edges.push_back(new Edge(vertices[28], vertices[33])); // 40
    edges.push_back(new Edge(vertices[34], vertices[28])); // 41
    edges.push_back(new Edge(vertices[29], vertices[34])); // 42
    edges.push_back(new Edge(vertices[35], vertices[29])); // 43
    edges.push_back(new Edge(vertices[30], vertices[35])); // 44
    edges.push_back(new Edge(vertices[36], vertices[30])); // 45
    edges.push_back(new Edge(vertices[31], vertices[36])); // 46
    edges.push_back(new Edge(vertices[37], vertices[31])); // 47
    edges.push_back(new Edge(vertices[32], vertices[37])); // 48
    edges.push_back(new Edge(vertices[33], vertices[38])); // 49
    edges.push_back(new Edge(vertices[39], vertices[34])); // 50
    edges.push_back(new Edge(vertices[40], vertices[35])); // 51
    edges.push_back(new Edge(vertices[41], vertices[36])); // 52
    edges.push_back(new Edge(vertices[37], vertices[42])); // 53
    edges.push_back(new Edge(vertices[38], vertices[43])); // 54
    edges.push_back(new Edge(vertices[43], vertices[39])); // 55
    edges.push_back(new Edge(vertices[39], vertices[44])); // 56
    edges.push_back(new Edge(vertices[44], vertices[40])); // 57
    edges.push_back(new Edge(vertices[40], vertices[45])); // 58
    edges.push_back(new Edge(vertices[45], vertices[41])); // 59
    edges.push_back(new Edge(vertices[41], vertices[46])); // 60
    edges.push_back(new Edge(vertices[46], vertices[42])); // 61
    edges.push_back(new Edge(vertices[47], vertices[43])); // 62
    edges.push_back(new Edge(vertices[48], vertices[44])); // 63
    edges.push_back(new Edge(vertices[49], vertices[45])); // 64
    edges.push_back(new Edge(vertices[46], vertices[50])); // 65
    edges.push_back(new Edge(vertices[51], vertices[47])); // 66
    edges.push_back(new Edge(vertices[48], vertices[51])); // 67
    edges.push_back(new Edge(vertices[52], vertices[48])); // 68
    edges.push_back(new Edge(vertices[49], vertices[52])); // 69
    edges.push_back(new Edge(vertices[53], vertices[49])); // 70
    edges.push_back(new Edge(vertices[50], vertices[53])); // 71
}

void Board::initTiles()
{

    vector<Vertex *> vertices0 = {vertices[0], vertices[4], vertices[8], vertices[12], vertices[7], vertices[3]};
    tiles.push_back(new Tile("mountains", "iron", vertices0, (size_t)10)); // 0

    vector<Vertex *> vertices1 = {vertices[1], vertices[5], vertices[9], vertices[13], vertices[8], vertices[4]};
    tiles.push_back(new Tile("pastures", "wool", vertices1, (size_t)2)); // 1

    vector<Vertex *> vertices2 = {vertices[2], vertices[6], vertices[10], vertices[14], vertices[9], vertices[5]};
    tiles.push_back(new Tile("forest", "wood", vertices2, (size_t)9)); // 2

    vector<Vertex *> vertices3 = {vertices[7], vertices[12], vertices[17], vertices[22], vertices[16], vertices[11]};
    tiles.push_back(new Tile("fields", "grain", vertices3, (size_t)12)); // 3

    vector<Vertex *> vertices4 = {vertices[8], vertices[13], vertices[18], vertices[23], vertices[17], vertices[12]};
    tiles.push_back(new Tile("hills", "brick", vertices4, (size_t)6)); // 4

    vector<Vertex *> vertices5 = {vertices[9], vertices[14], vertices[19], vertices[24], vertices[18], vertices[13]};
    tiles.push_back(new Tile("pastures", "wool", vertices5, (size_t)4)); // 5

    vector<Vertex *> vertices6 = {vertices[10], vertices[15], vertices[20], vertices[25], vertices[19], vertices[14]};
    tiles.push_back(new Tile("hills", "brick", vertices6, (size_t)10)); // 6

    vector<Vertex *> vertices7 = {vertices[16], vertices[22], vertices[28], vertices[33], vertices[27], vertices[21]};
    tiles.push_back(new Tile("fields", "grain", vertices7, (size_t)9)); // 7

    vector<Vertex *> vertices8 = {vertices[17], vertices[23], vertices[29], vertices[34], vertices[28], vertices[22]};
    tiles.push_back(new Tile("forest", "wood", vertices8, (size_t)11)); // 8

    vector<Vertex *> vertices9 = {vertices[18], vertices[24], vertices[30], vertices[35], vertices[29], vertices[23]};
    tiles.push_back(new Tile("desert", "", vertices9, (size_t)0)); // 9

    vector<Vertex *> vertices10 = {vertices[19], vertices[25], vertices[31], vertices[36], vertices[30], vertices[24]};
    tiles.push_back(new Tile("forest", "wood", vertices10, (size_t)3)); // 10

    vector<Vertex *> vertices11 = {vertices[20], vertices[26], vertices[32], vertices[37], vertices[31], vertices[25]};
    tiles.push_back(new Tile("mountains", "iron", vertices11, (size_t)8)); // 11

    vector<Vertex *> vertices12 = {vertices[28], vertices[34], vertices[39], vertices[43], vertices[38], vertices[33]};
    tiles.push_back(new Tile("forest", "wood", vertices12, (size_t)8)); // 12

    vector<Vertex *> vertices13 = {vertices[29], vertices[35], vertices[40], vertices[44], vertices[39], vertices[34]};
    tiles.push_back(new Tile("mountains", "iron", vertices13, (size_t)3)); // 13

    vector<Vertex *> vertices14 = {vertices[30], vertices[36], vertices[41], vertices[45], vertices[40], vertices[35]};
    tiles.push_back(new Tile("fields", "grain", vertices14, (size_t)4)); // 14

    vector<Vertex *> vertices15 = {vertices[31], vertices[37], vertices[42], vertices[46], vertices[41], vertices[36]};
    tiles.push_back(new Tile("pastures", "wool", vertices15, (size_t)5)); // 15

    vector<Vertex *> vertices16 = {vertices[39], vertices[44], vertices[48], vertices[51], vertices[47], vertices[43]};
    tiles.push_back(new Tile("hills", "brick", vertices16, (size_t)5)); // 16

    vector<Vertex *> vertices17 = {vertices[40], vertices[45], vertices[49], vertices[52], vertices[48], vertices[44]};
    tiles.push_back(new Tile("fields", "grain", vertices17, (size_t)6)); // 17

    vector<Vertex *> vertices18 = {vertices[41], vertices[46], vertices[50], vertices[53], vertices[49], vertices[45]};
    tiles.push_back(new Tile("pastures", "wool", vertices18, (size_t)11)); // 18
}

Board::Board()
{
    initVertices();
    initEdges();
    initTiles();
}

Board::~Board()
{
    for (auto vertex : vertices)
    {
        delete vertex;
    }
    vertices.clear();

    for (auto edge : edges)
    {
        delete edge;
    }
    edges.clear();

    for (auto tile : tiles)
    {
        delete tile;
    }
    tiles.clear();
}

vector<Vertex *> Board::getVertices()
{
    return this->vertices;
}
vector<Edge *> Board::getEdges()
{
    return this->edges;
}
vector<Tile *> Board::getTiles()
{
    return this->tiles;
}

bool Board::isAvailableVertex(size_t v)
{
    if (this->vertices[v]->getPlayer() == nullptr)
    {
        return true;
    }
    return false;
}

void Board::setPlayerAtVertex(size_t v, Player *p)
{
    this->getVertices()[v]->setPlayer(p);
}

void Board::setTypeAtVertex(size_t v, string s)
{
    this->getVertices()[v]->setType(s);
}

bool Board::isAvailableEdge(size_t e)
{
    if (this->edges[e]->getPlayer() == nullptr)
    {
        return true;
    }
    return false;
}

void Board::setPlayerAtEdge(size_t e, Player *p)
{
    this->getEdges()[e]->setPlayer(p);
}

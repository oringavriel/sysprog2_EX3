#include "Edge.hpp"
using namespace ariel;

size_t Edge::idCountEdge = 0;

Edge::Edge(Vertex *v1, Vertex *v2)
{
    this->v1 = v1;
    this->v2 = v2;
    this->index = idCountEdge++;
}
Vertex *Edge::getV1()
{
    return this->v1;
}
Vertex *Edge::getV2()
{
    return this->v2;
}
Player *Edge::getPlayer()
{
    return this->p;
}
void Edge::setPlayer(Player *p)
{
    this->p = p;
}
size_t Edge::getIndex()
{
    return this->index;
}
void Edge::resetIdCount()
{
    idCountEdge = 0;
}
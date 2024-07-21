#include "Vertex.hpp"
using namespace ariel;

size_t Vertex::idCountVertex = 0;

Vertex::Vertex()
{
    this->index = idCountVertex++;
}
Player *Vertex::getPlayer()
{
    return this->p;
}
void Vertex::setPlayer(Player *p)
{
    this->p = p;
}
string Vertex::getType()
{
    return this->type;
}
void Vertex::setType(string type)
{
    if (type == "settlement")
    {
        this->type = type;
    }
    else if (type == "city")
    {
        if (this->type == "settlement")
        {
            this->type = type;
        }
        else
        {
            cout << "you don't have a settlement here so you can't build a city" << endl;
        }
    }
    else
    {
        throw invalid_argument("invalid argument, try again");
    }
}
size_t Vertex::getIndex()
{
    return this->index;
}
void Vertex::resetIdCount()
{
    idCountVertex = 0;
}

#include "Tile.hpp"

using namespace ariel;

size_t Tile::idCountTile = 0;

Tile::Tile(string type, string resource, vector<Vertex *> vertices, size_t num)
{
    this->type = type;
    this->resource = resource;
    this->vertices = vertices;
    this->number = num;
    this->index = idCountTile++;
}
Tile::~Tile()
{
    vertices.clear();
}
string Tile::getType()
{
    return this->type;
}
string Tile::getResource()
{
    return this->resource;
}
vector<Vertex *> Tile::getVertices()
{
    return this->vertices;
}
size_t Tile::getNum()
{
    return this->number;
}
size_t Tile::getIndex()
{
    return this->index;
}
void Tile::resetIdCount()
{
    idCountTile = 0;
}

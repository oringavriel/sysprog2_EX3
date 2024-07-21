#include "Cards.hpp"
using namespace ariel;

Cards::Cards()
{
    this->cardsPack["knight card"] = 3;
    this->cardsPack["monopoly card"] = 5;
    this->cardsPack["build roads card"] = 5;
    this->cardsPack["year of plenty card"] = 5;
    this->cardsPack["victory point card"] = 4;
    this->cardsPack["biggest army card"] = 1;
}

map<string, int> Cards::getCardsPack()
{
    return this->cardsPack;
}

void Cards::reduceCard(string str)
{
    this->cardsPack[str]--;
}

vector<string> Cards::getCardTypes()
{
    vector<string> cardTypes = {"knight card", "monopoly card", "build roads card", "year of plenty card", "victory point card"};
    return cardTypes;
}

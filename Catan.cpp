#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include <iostream>

using namespace std;
using namespace ariel;

void Catan::setBoard()
{
    this->board = new Board();
}
void Catan::setCards()
{
    this->cards = new Cards();
}

Catan::Catan(Player &p1, Player &p2, Player &p3)
{
    this->players.push_back(&p1);
    this->players.push_back(&p2);
    this->players.push_back(&p3);
    setBoard();
    setCards();
}
Board *Catan::getBoard()
{
    return this->board;
}
Cards *Catan::getCards()
{
    return this->cards;
}

vector<Player *> Catan::getPlayers()
{
    return this->players;
}
Player *Catan::getCurrent()
{
    return this->current;
}
void Catan::setCurrent(Player *p)
{
    this->current = p;
}
void Catan::chooseStartingPlayer()
{
    this->current = players[0];
    cout << current->getName() << " is the starting player" << endl;
}
void Catan::turnSwitch()
{
    if (!victory(current))
    {
        if (this->current->getName() == this->players[0]->getName())
        {
            this->setCurrent(this->players[1]);
        }
        else if (this->current->getName() == this->players[1]->getName())
        {
            this->setCurrent(this->players[2]);
        }
        else if (this->current->getName() == this->players[2]->getName())
        {
            this->setCurrent(this->players[0]);
        }
    }
}
bool Catan::victory(Player *player)
{
    if (player->getPoints() >= 10)
    {
        printVictory(player);
        return true;
    }
    return false;
}
void Catan::printVictory(Player *player)
{
    cout << player->getName() << " won the game" << endl;
}

void Catan::sevenDice()
{
    for (size_t i = 0; i < 3; i++)
    {
        if (this->players[i]->totalResourceCount() > 7)
        {
            this->players[i]->returnHalf();
        }
    }
}

void Catan::rollDiceResourceAdd(int num)
{
    for (size_t i = 0; i < 19; i++)
    {
        if (this->board->getTiles()[i]->getNum() == num)
        {
            for (size_t t = 0; t < 3; t++)
            {
                for (size_t j = 0; j < 6; j++)
                {
                    if (this->board->getTiles()[i]->getVertices()[j]->getPlayer() == this->players[t])
                    {
                        if (this->board->getTiles()[i]->getVertices()[j]->getType() == "settlement")
                        {
                            this->players[t]->addResource(this->board->getTiles()[i]->getResource(), 1);
                        }
                        else if (this->board->getTiles()[i]->getVertices()[j]->getType() == "city")
                        {
                            this->players[t]->addResource(this->board->getTiles()[i]->getResource(), 2);
                        }
                    }
                }
            }
        }
    }
}

void Catan::rollDice(Player *player)
{
    if (this->current->getName() == player->getName())
    {
        int Dice1 = (rand() % 6) + 1;
        int Dice2 = (rand() % 6) + 1;
        int rollNum = (Dice1 + Dice2);
        cout << player->getName() << " got total dice roll of " << rollNum << endl;
        if (rollNum == 7)
        {
            sevenDice();
        }
        else if (rollNum != 9)
        {
            rollDiceResourceAdd(rollNum);
        }
    }
    else
    {
        throw invalid_argument("not player's turn");
    }
}

/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"
using namespace std;
using namespace ariel;

int main()
{
    Player p1("Dan");
    Player p2("Omer");
    Player p3("Michael");
    Catan catan(p1, p2, p3);
    // Starting of the game. Every player places two settlements and two roads.
    Board *board = catan.getBoard(); // get the board of the game.
    Cards *cardsPack = catan.getCards();
    p1.placeFirstSettlemnts(17, 20, board); // dan should get 2 brick, 1 wood, 1 grain, 1 iron
    p1.placeFirstRoads(25, 32, board);
    p2.placeFirstSettlemnts(35, 41, board); // omer should get 2 grain, 1 iron, 2 wool
    p2.placeFirstRoads(43, 60, board);
    try
    {
        p3.placeFirstSettlemnts(35, 11, board); // p3 tries to place a settlement in the same location as p2.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl; // should print vertices are not available
    }
    p3.placeFirstSettlemnts(6, 7, board); // michael should get 1 wood, 1 grain , 1 iron
    p3.placeFirstRoads(9, 10, board);
    catan.chooseStartingPlayer(); // should print the name of the starting player- dan.
    p1.rollDice(&catan);
    p1.placeRoad(19, board);
    catan.turnSwitch();
    p2.rollDice(&catan);
    try
    {
        p2.placeSettlement(29, board); // p3 tries to place a settlement in the same location as p2.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl; // should print not enough resources
    }
    p2.buyCard(*cardsPack);
    catan.turnSwitch();
    p3.rollDice(&catan);
    catan.turnSwitch();
}
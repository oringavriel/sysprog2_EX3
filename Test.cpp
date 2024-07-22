#include <vector>
#include <sstream>
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Tile.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include <stdexcept>
#include "doctest.h"
#include <iostream>
using namespace ariel;
using namespace std;
using namespace doctest;

TEST_CASE("test vertex init")
{
    Vertex::resetIdCount();
    Vertex v;
    CHECK((v.getIndex() == 0) == true);
    CHECK((v.getPlayer() == nullptr) == true);
    Player p("dan");
    v.setPlayer(&p);
    CHECK((v.getPlayer() == &p) == true);
    CHECK((v.getType() == "") == true);
    string expected = "you don't have a settlement here so you can't build a city";
    stringstream output;
    streambuf *coutBuf;
    v.setType("city");
    coutBuf = cout.rdbuf(output.rdbuf());
    CHECK((output.str().compare(expected)) == true);
    cout.rdbuf(coutBuf);
    CHECK((v.getType() == "") == true);
    v.setType("settlement");
    CHECK((v.getType() == "settlement") == true);
    v.setType("city");
    CHECK((v.getType() == "city") == true);
}

TEST_CASE("test edge init")
{
    Vertex v1, v2;
    Edge e(&v1, &v2);
    CHECK(e.getV1() == &v1);
    CHECK_FALSE(e.getV2() == &v1);
    CHECK(e.getV2() == &v2);
    Player p("dan");
    e.setPlayer(&p);
    CHECK(e.getPlayer() == &p);
    CHECK(e.getIndex() == 0);
}

TEST_CASE("test tile init")
{
    Vertex::resetIdCount();
    Edge::resetIdCount();
    Tile::resetIdCount();
    Vertex v1, v2, v3, v4, v5, v6;
    vector<Vertex *> vertices = {&v1, &v2, &v3, &v4, &v5, &v6};
    Tile t("forest", "wood", vertices, 3);
    CHECK(t.getType() == "forest");
    CHECK(t.getResource() == "wood");
    CHECK(t.getVertices()[3]->getIndex() == 3);
    CHECK(t.getNum() == 3);
    CHECK(t.getIndex() == 0);
}

TEST_CASE("test board init")
{
    Vertex::resetIdCount();
    Edge::resetIdCount();
    Tile::resetIdCount();
    Board b;
    CHECK(b.getEdges()[2]->getIndex() == 2);
    CHECK(b.getEdges()[28]->getV1()->getIndex() == 18);
    CHECK(b.getTiles()[9]->getResource() == "");
    CHECK(b.getTiles()[10]->getIndex() == 10);
    CHECK(b.getTiles()[10]->getResource() == "wood");
    CHECK(b.getTiles()[10]->getType() == "forest");
    CHECK(b.getTiles()[10]->getNum() == 3);
    Vertex *v1 = b.getTiles()[10]->getVertices()[2];
    CHECK(v1->getIndex() == 31);
    Player p1("dan");
    CHECK(b.isAvailableEdge(2) == true);
    b.setPlayerAtEdge(2, &p1);
    CHECK(b.isAvailableEdge(2) == false);
    CHECK(b.isAvailableVertex(2) == true);
    b.setPlayerAtVertex(2, &p1);
    CHECK(b.isAvailableVertex(2) == false);
    b.setTypeAtVertex(2, "settlement");
    CHECK(b.getVertices()[2]->getType() == "settlement");
}

TEST_CASE("test catan init and getters and setters")
{
    Vertex::resetIdCount();
    Edge::resetIdCount();
    Tile::resetIdCount();
    Player p1("dan");
    Player p2("omer");
    Player p3("michael");
    Catan catan(p1, p2, p3);
    Board *b = catan.getBoard();
    CHECK(b->getTiles()[0]->getNum() == 10);
    catan.setCurrent(&p2);
    CHECK(catan.getCurrent()->getName() == "omer");
    catan.chooseStartingPlayer();
    CHECK(catan.getCurrent()->getName() == "dan");
    CHECK(catan.getPlayers()[2]->getName() == "michael");
    catan.turnSwitch();
    CHECK(catan.getCurrent()->getName() == "omer");
    p1.addPoints(10);
    catan.turnSwitch(); // not dan's turn
    CHECK(catan.victory(&p1) == true);
}

TEST_CASE("test player init getters and setters")
{
    Vertex::resetIdCount();
    Edge::resetIdCount();
    Tile::resetIdCount();
    Player p1("dan");
    Player p2("omer");
    Player p3("michael");
    Catan catan(p1, p2, p3);
    Board *b = catan.getBoard();
    p1.addResource("wood", 1);
    CHECK(p1.getResources()["wood"] == 1);
    CHECK_THROWS(p1.reduceResource("wood", 2)); // test reduce more than what player has
    p1.reduceResource("wood", 1);
    CHECK(p1.getResources()["wood"] == 0);
}

TEST_CASE("test player place first settlements and roads")
{
    Vertex::resetIdCount();
    Edge::resetIdCount();
    Tile::resetIdCount();
    Player p1("dan");
    Player p2("omer");
    Player p3("michael");
    Catan catan(p1, p2, p3);
    Board *b = catan.getBoard();
    p1.placeFirstSettlemnts(4, 14, b);
    CHECK(p1.getPoints() == 2);
    CHECK(b->getVertices()[4]->getPlayer()->getName() == "dan");
    CHECK(p1.getResources()["iron"] == 1);
    CHECK(p1.getResources()["wool"] == 2);
    CHECK(p1.getResources()["brick"] == 1);
    CHECK(p1.getResources()["wood"] == 1);
    CHECK_THROWS(p2.placeFirstSettlemnts(2, 4, b)); // test p2 place first settlements in taken vertex 
    p2.placeFirstSettlemnts(15, 2, b);
    CHECK_THROWS(p1.placeFirstRoads(1, 42, b)); // test p1 place first roads in not close edge
    p1.placeFirstRoads(1, 15, b);
    CHECK(b->getEdges()[1]->getPlayer() == &p1);
    p2.placeFirstRoads(5, 17, b);
}

TEST_CASE("test init of cardspack and usage")
{
    Vertex::resetIdCount();
    Edge::resetIdCount();
    Tile::resetIdCount();
    Player p1("dan");
    Player p2("omer");
    Player p3("michael");
    Catan catan(p1, p2, p3);
    Board *b = catan.getBoard();
    p1.addResource("iron", 2);
    p1.addResource("wool", 2);
    p1.addResource("grain", 3);
    p1.buyCard(*catan.getCards());
    p1.buyCard(*catan.getCards());
    CHECK_THROWS(p1.buyCard(*catan.getCards())); // test when player doesn't have enough resources
    p1.printResourceMap();
    p1.printCardMap();

    SUBCASE("test useVictoryPointCard")
    {
        CHECK_THROWS(p1.useVictoryPointCard(&catan)); //test when player doesn't have this card
        p1.addCard("victory point card", 1);
        CHECK((p1.getCards()["victory point card"] == 1) == true);
        catan.setCurrent(&p1);
        p1.useVictoryPointCard(&catan);
        CHECK((p1.getPoints() == 1) == true);
        CHECK((p1.getCards()["victory point card"] == 0) == true);
    }

    SUBCASE("test useYearOfPlentyCard(")
    {
        CHECK_THROWS(p1.useYearOfPlentyCard("wood", "wool", &catan)); //test when player doesn't have this card
        p1.addCard("year of plenty card", 1);
        catan.setCurrent(&p1);
        p1.useYearOfPlentyCard("wood", "wool", &catan);
        CHECK(p1.getResources()["wood"] == 1);
        CHECK(p1.getResources()["wool"] == 1);
        CHECK(p1.getCards()["year of plenty card"] == 0);
    }

    SUBCASE("test useMonopolyCard")
    {
        p2.addResource("wood", 2);
        p3.addResource("wool", 2);
        vector<Player *> players = catan.getPlayers();
        CHECK_THROWS(p1.useMonopolyCard(players, "wood", &catan));//test when player doesn't have this card
        p1.addCard("monopoly card", 1);
        CHECK(p1.getCards()["monopoly card"] == 1);
        catan.setCurrent(&p1);
        p1.useMonopolyCard(players, "wood", &catan);
        CHECK(p1.getResources()["wood"] == 1);
        CHECK(p1.getCards()["monopoly card"] == 0);
    }

    SUBCASE("test useBuildRoadsCard")
    {
        CHECK_THROWS(p1.useBuildRoadsCard(14, 2, b, &catan));//test when player doesn't have this card
        p2.addCard("build roads card", 1);
        CHECK(p1.getCards()["build roads card"] == 1);
        p2.placeFirstSettlemnts(7, 4, b);
        p2.placeFirstRoads(1, 6, b);
        p1.placeFirstSettlemnts(9, 22, b);
        p1.placeFirstRoads(15, 34, b);
        catan.setCurrent(&p2);
        CHECK_THROWS(p2.useBuildRoadsCard(15, 60, b, &catan)); // p1 is already in edge number 15
        catan.setCurrent(&p2);
        CHECK_THROWS(p2.useBuildRoadsCard(8, 11, b, &catan)); // 8 is not near edge or settlement
        catan.setCurrent(&p2);
        p2.useBuildRoadsCard(0, 10, b, &catan);
        CHECK(b->getEdges()[10]->getPlayer()->getName() == "omer");
        CHECK(p2.getCards()["build roads card"] == 0);
    }
}

TEST_CASE("test place road")
{
    Vertex::resetIdCount();
    Edge::resetIdCount();
    Tile::resetIdCount();
    Player p1("dan");
    Player p2("omer");
    Player p3("michael");
    Catan catan(p1, p2, p3);
    Board *b = catan.getBoard();
    p1.addResource("brick", 4);
    p1.addResource("wood", 4);
    p2.addResource("wool", 4);
    p2.addResource("wood", 4);
    p2.addResource("grain", 3);
    p3.addResource("iron", 7);
    p3.addResource("brick", 4);
    p3.addResource("wood", 4);
    p3.addResource("grain", 5);
    p1.placeFirstSettlemnts(12, 27, b); // 1 iron 1 brick 2 grain
    p1.placeFirstRoads(19, 39, b);
    p2.placeFirstSettlemnts(31, 49, b); // 1 iron 1 wood 2 wool 1 grain
    p2.placeFirstRoads(37, 70, b);
    p3.placeFirstSettlemnts(34, 52, b); // 2 wood 1 iron 1 grain
    p3.placeFirstRoads(50, 68, b);

    SUBCASE("test placing in others player road")
    {
        CHECK_THROWS(p1.placeRoad(37, b));
    }
    SUBCASE("test placing when there isn't enough resources")
    {
        CHECK_THROWS(p2.placeRoad(48, b));
    }
    SUBCASE("test placing when the road is not near other road/settlement")
    {
        p2.addResource("brick", 3);
        CHECK_THROWS(p2.placeRoad(3, b));
    }
    SUBCASE("place road correctly")
    {
        p3.placeRoad(42, b); // road near road
        CHECK((b->getEdges()[42]->getPlayer()->getName() == "michael") == true);
        p2.addResource("brick", 3);
        p2.placeRoad(69, b); // road near settlement
        CHECK(b->getEdges()[69]->getPlayer()->getName() == "omer");
    }
}

TEST_CASE("test place settlement and place city")
{
    Vertex::resetIdCount();
    Edge::resetIdCount();
    Tile::resetIdCount();
    Player p1("dan");
    Player p2("omer");
    Player p3("michael");
    Catan catan(p1, p2, p3);
    Board *b = catan.getBoard();
    p1.addResource("brick", 4);
    p1.addResource("wood", 4);
    p2.addResource("wool", 4);
    p2.addResource("wood", 4);
    p2.addResource("grain", 3);
    p2.addResource("brick", 4);
    p3.addResource("iron", 7);
    p3.addResource("brick", 4);
    p3.addResource("wool", 5);
    p3.addResource("wood", 4);
    p3.addResource("grain", 5);
    p1.placeFirstSettlemnts(12, 27, b); // 1 iron 1 brick 2 grain
    p1.placeFirstRoads(19, 39, b);
    p2.placeFirstSettlemnts(28, 49, b); // 1 iron 1 wood 2 wool 1 grain
    p2.placeFirstRoads(34, 70, b);
    p3.placeFirstSettlemnts(29, 52, b); // 2 wood 1 iron 1 grain
    p3.placeFirstRoads(42, 68, b);

    SUBCASE("not enough resources")
    {
        CHECK_THROWS(p1.placeSettlement(20, b));
    }
    SUBCASE("player's vertex")
    {
        CHECK_THROWS(p3.placeSettlement(34, b));
    }
    SUBCASE("check distance isn't enough from other settlement")
    {
        CHECK_THROWS(p3.placeSettlement(34, b));
    }
    SUBCASE("no road leading to the settlement")
    {
        CHECK_THROWS(p3.placeSettlement(18, b));
    }
    SUBCASE("placing settlement near other player's road")
    {
        CHECK_THROWS(p3.placeSettlement(17, b));
    }

    p2.placeRoad(24, b);
    p2.placeSettlement(16, b);
    p2.placeRoad(18, b);
    CHECK_THROWS(p2.placeSettlement(11, b)); // placing noy by law of distance

    SUBCASE("not enough resources")
    {
        CHECK_THROWS(p2.placeCity(16, b));
    }
    p2.addResource("grain", 4);
    p2.addResource("iron", 4);
    p2.placeCity(16, b);
    CHECK(b->getVertices()[16]->getType() == "city");
    CHECK(b->getVertices()[16]->getPlayer()->getName() == "omer");
}

TEST_CASE("test roll dice")
{
    Vertex::resetIdCount();
    Edge::resetIdCount();
    Tile::resetIdCount();
    Player p1("dan");
    Player p2("omer");
    Player p3("michael");
    Catan catan(p1, p2, p3);
    Board *b = catan.getBoard();
    catan.chooseStartingPlayer();
    p1.rollDice(&catan);
    catan.turnSwitch();
    CHECK_THROWS(p3.rollDice(&catan));// test not p3 turn
    p2.rollDice(&catan);

    SUBCASE("test sevenDice")
    {
        p1.addResource("wood", 8);
        p1.addResource("wool", 3);
        p1.addResource("brick", 1);
        p1.addResource("grain", 3);
        p2.addResource("wood", 6);

        stringstream input;
        streambuf *cinBuf = cin.rdbuf(input.rdbuf());
        input << "woor" << endl;
        input << "5" << endl;
        input << "wood" << endl;
        input << "6" << endl;
        input << "wool" << endl;
        input << "1" << endl;
        catan.sevenDice();
        CHECK(p1.getResources()["wood"] == 2);
        CHECK(p1.getResources()["wool"] == 2);
        CHECK(p2.getResources()["wood"] == 6);
    }

    SUBCASE("test rollDiceResourceAdd")
    {
        p1.placeFirstSettlemnts(4, 14, b);
        p2.placeFirstSettlemnts(15, 2, b);
        p3.placeFirstSettlemnts(35, 49, b);
        p1.placeFirstRoads(1, 15, b);
        p2.placeFirstRoads(5, 17, b);
        p3.placeFirstRoads(70, 51, b);
        catan.rollDiceResourceAdd(10);
        CHECK(p1.getResources()["iron"] == 2);
        CHECK(p1.getResources()["brick"] == 2);
        CHECK(p2.getResources()["brick"] == 2);
        CHECK(p3.getResources()["iron"] == 1);
    }
}

TEST_CASE("test tradeResources")
{
    Vertex::resetIdCount();
    Edge::resetIdCount();
    Tile::resetIdCount();
    Player p1("dan");
    Player p2("omer");
    Player p3("michael");
    Catan catan(p1, p2, p3);
    Board *b = catan.getBoard();

    SUBCASE("test valid tradeResources")
    {
        p1.addResource("wood", 2);
        p2.addResource("wool", 3);
        catan.chooseStartingPlayer();
        string input = "yes";
        stringstream ss(input);
        cin.rdbuf(ss.rdbuf());
        p1.tradeResources(&catan, &p2, "wood", 1, "wool", 2);
        cin.rdbuf(nullptr);

        SUBCASE("test trade when it's not ther player's turn")
        {
            try
            {
                p2.tradeResources(&catan, &p2, "wood", 1, "wool", 1);
            }
            catch (const std::exception &e)
            {
                cout << e.what() << endl;
            }
        }
        SUBCASE("test trade when there's not enough resources")
        {
            try
            {
                string input = "yes";
                stringstream ss(input);
                cin.rdbuf(ss.rdbuf());
                p1.tradeResources(&catan, &p2, "grain", 1, "wool", 1);
                cin.rdbuf(nullptr);
            }
            catch (const std::exception &e)
            {
                cout << e.what() << endl; // should print not enough resources
            }
        }
    }
}

TEST_CASE("test tradeCards")
{
    Vertex::resetIdCount();
    Edge::resetIdCount();
    Tile::resetIdCount();
    Player p1("dan");
    Player p2("omer");
    Player p3("michael");
    Catan catan(p1, p2, p3);
    Board *b = catan.getBoard();

    SUBCASE("test valid tradeResources")
    {
        p1.addCard("monopoly card", 2);
        p2.addCard("victory point card", 2);
        catan.chooseStartingPlayer();
        string input = "yes";
        stringstream ss(input);
        cin.rdbuf(ss.rdbuf());
        p1.tradeCards(&catan, &p2, "monopoly card", 1, "victory point card", 1);
        cin.rdbuf(nullptr);

        SUBCASE("test trade when it's not ther player's turn")
        {
            try
            {
                p2.tradeCards(&catan, &p2, "monopoly card", 1, "victory point card", 1);
            }
            catch (const std::exception &e)
            {
                cout << e.what() << endl;
            }
        }
        SUBCASE("test trade when there's not enough resources")
        {
            try
            {
                string input = "yes";
                stringstream ss(input);
                cin.rdbuf(ss.rdbuf());
                p1.tradeCards(&catan, &p2, "victory point card", 1, "monopoly card", 3);
                cin.rdbuf(nullptr);
            }
            catch (const std::exception &e)
            {
                cout << e.what() << endl; // should print not enough cards
            }
        }
    }
}
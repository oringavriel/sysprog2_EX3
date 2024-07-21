#include "Player.hpp"

using namespace std;
using namespace ariel;

void Player::initCards()
{
    this->cards["knight card"] = 0;
    this->cards["monopoly card"] = 0;
    this->cards["build roads card"] = 0;
    this->cards["year of plenty card"] = 0;
    this->cards["victory point card"] = 0;
    this->cards["biggest army card"] = 0;
}

void Player::initResources()
{
    this->resources["wood"] = 0;
    this->resources["brick"] = 0;
    this->resources["wool"] = 0;
    this->resources["grain"] = 0;
    this->resources["iron"] = 0;
}

Player::Player(string name)
{
    this->name = name;
    this->points = 0;
    initResources();
    initCards();
}

int Player::getPoints()
{
    return this->points;
}
void Player::addPoints(int num)
{
    this->points += num;
}

void Player::printPoints()
{
    cout << this->name << " has " << this->points << " points";
}

void Player::printResourceMap()
{
    cout << "wood : " << this->resources["wood"] << endl;
    cout << "brick : " << this->resources["brick"] << endl;
    cout << "wool : " << this->resources["wool"] << endl;
    cout << "grain : " << this->resources["grain"] << endl;
    cout << "iron : " << this->resources["iron"] << endl;
}

void Player::printCardMap()
{
    cout << "knight card : " << this->cards["knight card"] << endl;
    cout << "victory point card : " << this->cards["victory point card"] << endl;
    cout << "monopoly card : " << this->cards["monopoly card"] << endl;
    cout << "build roads card : " << this->cards["build roads card"] << endl;
    cout << "year of plenty card : " << this->cards["year of plenty card"] << endl;
    cout << "biggest army card : " << this->cards["biggest army card"] << endl;
}
string Player::getName()
{
    return this->name;
}

map<string, int> Player::getCards()
{
    return this->cards;
}

void Player::addCard(string card, int amount)
{
    this->cards[card] += amount;
}
void Player::reduceCard(string card, int amount)
{
    this->cards[card] -= amount;
}

map<string, int> Player::getResources()
{
    return this->resources;
}

void Player::reduceResource(string resource, int num)
{
    if (num > this->resources[resource])
    {
        throw invalid_argument("number to reduce is bigger than the number of resources the player has");
    }
    this->resources[resource] -= num;
    ;
}

void Player::addResource(string resource, int num)
{
    this->resources[resource] += num;
    cout << this->name << " was added " << num << " " << resource << endl;
}

int Player::totalResourceCount()
{
    int count = 0;
    count += this->resources["wood"];
    count += this->resources["brick"];
    count += this->resources["wool"];
    count += this->resources["grain"];
    count += this->resources["iron"];
    return count;
}

void Player::placeFirstSettlemnts(size_t vertexNum1, size_t vertexNum2, Board *b)
{
    if (b->isAvailableVertex(vertexNum1) == false || b->isAvailableVertex(vertexNum2) == false)
    {
        throw invalid_argument("vertices are not available");
    }
    else
    {
        b->setPlayerAtVertex(vertexNum1, this);
        b->setPlayerAtVertex(vertexNum2, this);
        b->setTypeAtVertex(vertexNum1, "settlement");
        b->setTypeAtVertex(vertexNum2, "settlement");
        this->points += 2;
        cout << this->name << " added 2 settlements in vertices " << vertexNum1 << ", " << vertexNum2 << endl;
        cout << this->name << " was added 2 points" << endl;
        for (size_t i = 0; i < 19; i++)
        {
            for (size_t j = 0; j < 6; j++)
            {
                if ((b->getTiles()[i]->getVertices()[j]->getIndex() == vertexNum1 ||
                     b->getTiles()[i]->getVertices()[j]->getIndex() == vertexNum2) &&
                    b->getTiles()[i]->getResource() != "")
                {
                    this->addResource(b->getTiles()[i]->getResource(), 1);
                }
            }
        }
    }
}

void Player::placeFirstRoads(size_t edgeNum1, size_t edgeNum2, Board *b)
{
    if (b->isAvailableEdge(edgeNum1) == false || b->isAvailableEdge(edgeNum2) == false)
    {
        throw invalid_argument("edges are not available");
    }
    else if ((b->getEdges()[edgeNum1]->getV1()->getPlayer() != this &&
              b->getEdges()[edgeNum1]->getV2()->getPlayer() != this) ||
             (b->getEdges()[edgeNum2]->getV1()->getPlayer() != this &&
              b->getEdges()[edgeNum2]->getV2()->getPlayer() != this))
    {
        throw invalid_argument("edges are not valid");
    }
    else
    {
        b->setPlayerAtEdge(edgeNum1, this);
        b->setPlayerAtEdge(edgeNum2, this);
        cout << this->name << " added 2 roads in edges " << edgeNum1 << ", " << edgeNum2 << endl;
    }
}

void Player::addBiggestArmyCard(Cards &cardsPack)
{
    if (cardsPack.getCardsPack()["biggest army card"] == 0)
    {
        cout << "the biggest army card is on other player's posetion" << endl;
    }
    else
    {
        cardsPack.reduceCard("biggest army card");
        this->cards["biggest army card"]++;
        this->points += 2;
    }
}

void Player::buyCard(Cards &cardsPack)
{
    if (this->resources["iron"] == 0 || this->resources["grain"] == 0 || this->resources["wool"] == 0)
    {
        throw invalid_argument("not enough resources");
    }
    else
    {
        this->reduceResource("iron", 1);
        this->reduceResource("wool", 1);
        this->reduceResource("grain", 1);
        size_t RandomIndex = (size_t)rand() % cardsPack.getCardTypes().size();
        string chosenType = cardsPack.getCardTypes()[RandomIndex];
        while (cardsPack.getCardsPack()[chosenType] == 0)
        {
            RandomIndex = (size_t)rand() % cardsPack.getCardTypes().size();
            chosenType = cardsPack.getCardTypes()[RandomIndex];
        }
        cardsPack.getCardsPack()[chosenType]--;
        this->cards[chosenType]++;
        cout << "the card " << this->name << "  got is : " << chosenType << endl;
        if (chosenType == "knight card" && this->cards["knight card"] == 3)
        {
            addBiggestArmyCard(cardsPack);
        }
    }
}

void Player::useVictoryPointCard(Catan *catan)
{
    if (this->cards["victory point card"] == 0)
    {
        throw invalid_argument("No victory point cards");
    }
    else
    {
        this->cards["victory point card"]--;
        this->points++;
        cout << this->name << "used victory point card" << endl;
        this->printPoints();
        catan->turnSwitch();
    }
}

void Player::useYearOfPlentyCard(string resource1, string resource2, Catan *catan)
{
    if (this->cards["year of plenty card"] == 0)
    {
        throw invalid_argument("No year of plenty cards");
    }
    else if (this->resources.find(resource1) == this->resources.end() ||
             this->resources.find(resource2) == this->resources.end())
    {
        throw invalid_argument("Invalid resource");
    }
    else
    {
        cout << this->name << "used year of plenty card" << endl;
        this->addResource(resource1, 1);
        this->addResource(resource2, 1);
        this->cards["year of plenty card"]--;
        catan->turnSwitch();
    }
}

void Player::useMonopolyCard(vector<Player *> players, string resource, Catan *catan)
{
    if (this->cards["monopoly card"] == 0)
    {
        throw invalid_argument(" No monopoly cards");
    }
    else if (this->resources.find(resource) == this->resources.end())
    {
        throw invalid_argument("Invalid resource");
    }
    else
    {
        cout << this->name << "used monopoly card" << endl;
        for (size_t i = 0; i < 3; i++)
        {
            if (players[i]->getName() != this->name)
            {
                if (players[i]->getResources()[resource] > 0)
                {
                    players[i]->reduceResource(resource, 1);
                    this->addResource(resource, 1);
                }
            }
        }
        this->cards["monopoly card"]--;
        catan->turnSwitch();
    }
}

void Player::useBuildRoadsCard(size_t edgeNum1, size_t edgeNum2, Board *b, Catan *catan)
{
    if (this->cards["build roads card"] == 0)
    {
        throw invalid_argument("No build roads cards");
    }
    else
    {
        cout << this->name << "used build roads card" << endl;
        placeTwoRoadsBuildCard(edgeNum1, edgeNum2, b);
        this->cards["build roads card"]--;
        catan->turnSwitch();
    }
}

bool Player::checkEdgeNearEdge(size_t edgeNum, Board *b)
{
    for (Edge *e : b->getEdges())
    {
        if (e->getIndex() != edgeNum)
        {
            if (e->getV1() == b->getEdges()[edgeNum]->getV1())
            {
                if (e->getPlayer() == this)
                {
                    return true;
                }
            }
            if (e->getV1() == b->getEdges()[edgeNum]->getV2())
            {
                if (e->getPlayer() == this)
                {
                    return true;
                }
            }
            if (e->getV2() == b->getEdges()[edgeNum]->getV1())
            {
                if (e->getPlayer() == this)
                {
                    return true;
                }
            }
            if (e->getV2() == b->getEdges()[edgeNum]->getV2())
            {
                if (e->getPlayer() == this)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void Player::placeRoad(size_t edgeNum, Board *b)
{
    bool isValid = false;
    if (this->resources["brick"] == 0 || this->resources["wood"] == 0)
    {
        throw invalid_argument("not enough resources");
    }
    else if (b->getEdges()[edgeNum]->getPlayer() != nullptr)
    {
        throw invalid_argument("edge isn't available");
    }
    else
    {
        if ((b->getEdges()[edgeNum]->getV1()->getPlayer() == this ||
             b->getEdges()[edgeNum]->getV2()->getPlayer() == this) || // there's a near settlement
            checkEdgeNearEdge(edgeNum, b))
        {
            isValid = true;
        }
        if (isValid == false)
        {
            throw invalid_argument("edge needs to be next to your settlement/road ");
        }
        else if (isValid == true)
        {
            this->reduceResource("brick", 1);
            this->reduceResource("wood", 1);
            b->getEdges()[edgeNum]->setPlayer(this);
            cout << this->name << " added road in edge number " << edgeNum << endl;
        }
    }
}

void Player::placeTwoRoadsBuildCard(size_t edgeNum1, size_t edgeNum2, Board *b)
{
    bool isValid = false;
    if (b->getEdges()[edgeNum1]->getPlayer() != nullptr ||
        b->getEdges()[edgeNum2]->getPlayer() != nullptr)
    {
        throw invalid_argument("edge isn't available");
    }
    else
    {
        if ((b->getEdges()[edgeNum1]->getV1()->getPlayer() == this ||
             b->getEdges()[edgeNum1]->getV2()->getPlayer() == this) &&
            (b->getEdges()[edgeNum2]->getV1()->getPlayer() == this ||
             b->getEdges()[edgeNum2]->getV2()->getPlayer() == this))
        {
            isValid = true;
        }
        else
        {
            bool isValid1 = false;
            bool isValid2 = false;
            isValid1 = checkEdgeNearEdge(edgeNum1, b);
            isValid2 = checkEdgeNearEdge(edgeNum2, b);
            if (isValid1 && isValid2)
            {
                isValid = true;
            }
        }
        if (isValid == false)
        {
            throw invalid_argument("edge needs to be next to your settlement/road ");
        }
        if (isValid == true)
        {
            b->getEdges()[edgeNum1]->setPlayer(this);
            b->getEdges()[edgeNum2]->setPlayer(this);
            cout << this->name << "added roads by monopoly card in edges " << edgeNum1 << " ," << edgeNum2 << endl;
        }
    }
}

bool Player::checkDistance(size_t vertexNum, Board *b)
{
    for (Edge *e : b->getEdges())
    {
        if (e->getV1()->getIndex() == vertexNum)
        {
            if (e->getV2()->getPlayer() != nullptr)
            {
                return false;
            }
        }
        else if (e->getV2()->getIndex() == vertexNum)
        {
            if (e->getV1()->getPlayer() != nullptr)
            {
                return false;
            }
        }
    }
    return true;
}

void Player::placeSettlement(size_t vertexNum, Board *b)
{
    bool isValid = false;
    if (this->resources["brick"] == 0 || this->resources["wood"] == 0 ||
        this->resources["grain"] == 0 || this->resources["wool"] == 0)
    {
        throw invalid_argument("not enough resources");
    }
    else if (b->getVertices()[vertexNum]->getPlayer() != nullptr)
    {
        throw invalid_argument("vertex isn't available");
    }
    else if (checkDistance(vertexNum, b) == false)
    {
        throw invalid_argument("vertex isn't 2 roads far from another settlement");
    }
    else
    {
        for (Edge *e : b->getEdges())
        {
            if ((e->getV1() == b->getVertices()[vertexNum] || e->getV2() == b->getVertices()[vertexNum]) && e->getPlayer() == this)
            {
                isValid = true;
            }
        }
        if (isValid == false)
        {
            throw invalid_argument("settlement place isn't near a road");
        }
        else if (isValid == true)
        {
            this->reduceResource("brick", 1);
            this->reduceResource("wood", 1);
            this->reduceResource("grain", 1);
            this->reduceResource("wool", 1);
            b->setPlayerAtVertex(vertexNum, this);
            b->setTypeAtVertex(vertexNum, "settlement");
            this->points++;
            cout << this->name << " added setttlement in vertex number " << vertexNum << " and 1 point was added to him" << endl;
        }
    }
}

void Player::placeCity(size_t vertexNum, Board *b)
{
    if (b->getVertices()[vertexNum]->getPlayer() != this)
    {
        throw invalid_argument("cities are built only on *your* settlements");
    }
    else if (this->resources["grain"] < 2 || this->resources["iron"] < 3)
    {
        throw invalid_argument("not enough resources");
    }
    else
    {
        this->reduceResource("grain", 2);
        this->reduceResource("iron", 3);
        b->getVertices()[vertexNum]->setType("city");
        cout << this->name << " built a city in vertex " << vertexNum << " and 1 point was added to him" << endl;
        this->points++;
    }
}

void Player::rollDice(Catan *c)
{
    c->rollDice(this);
}

void Player::returnHalf()
{
    int total = this->totalResourceCount();
    int totalReturned = 0;
    string resource;
    int numToReturn = 0;
    cout << this->name << ", you should return " << total / 2 << " resources" << endl;
    while (totalReturned < total / 2)
    {
        cout << "Enter the resource you want to return" << endl;
        cin >> resource;
        cout << "Enter the amount of that resource that you want to return" << endl;
        cin >> numToReturn;
        if (this->resources.find(resource) == this->resources.end())
        {
            cout << "invalid resource" << endl;
        }
        else if (numToReturn > this->getResources()[resource])
        {
            cout << "not enough resources";
        }
        else
        {
            this->reduceResource(resource, numToReturn);
            totalReturned += numToReturn;
        }
    }
}

void Player::tradeResources(Catan *catan, Player *other, string thisResource, int thisAmount, string otherResource, int otherAmount)
{
    if (catan->getCurrent()->getName() == this->getName())
    {
        string answer;
        cout << this->getName() << " wants to trade with " << other->getName() << ": " << thisAmount << " " << thisResource << " for " << otherAmount << " " << otherResource << endl;
        cout << other->getName() << ". Would you like to trade? answer yes or no" << endl;
        cin >> answer;
        if (answer == "yes")
        {
            if (this->resources[thisResource] < thisAmount)
            {
                throw invalid_argument("You don't have enough to trade.");
            }
            if (other->resources[otherResource] < otherAmount)
            {
                throw invalid_argument("The other player doesn't have enough to trade.");
            }
            else
            {
                this->reduceResource(thisResource, thisAmount);
                this->addResource(otherResource, otherAmount);
                other->addResource(thisResource, thisAmount);
                other->reduceResource(otherResource, otherAmount);
                cout << this->getName() << " traded with " << other->getName() << ": " << thisAmount << " " << thisResource << " for " << otherAmount << " " << otherResource << endl;
            }
        }
        else
        {
            cout << other->getName() << " doesn't want to trade" << endl;
        }
    }
    else
    {
        throw invalid_argument("it's not your turn, you can't trade");
    }
}

void Player::tradeCards(Catan *catan, Player *other, string thisCard, int thisAmount, string otherCard, int otherAmount)
{
    if (catan->getCurrent()->getName() == this->getName())
    {
        string answer;
        cout << this->getName() << " wants to trade with " << other->getName() << ": " << thisAmount << " " << thisCard << " for " << otherAmount << " " << otherCard << endl;
        cout << other->getName() << ". Would you like to trade? answer yes or no" << endl;
        cin >> answer;
        if (answer == "yes")
        {
            if (this->cards[thisCard] < thisAmount)
            {
                throw invalid_argument("You don't have enough to trade.");
            }
            if (other->getCards()[otherCard] < otherAmount)
            {
                throw invalid_argument("The other player doesn't have enough to trade.");
            }
            else
            {
                this->reduceCard(thisCard, thisAmount);
                this->addCard(otherCard, otherAmount);
                other->addCard(thisCard, thisAmount);
                other->reduceCard(otherCard, otherAmount);
                cout << this->getName() << " traded with " << other->getName() << ": " << thisAmount << " " << thisCard << " for " << otherAmount << " " << otherCard << endl;
            }
        }
        else
        {
            cout << other->getName() << " doesn't want to trade" << endl;
        }
    }
    else
    {
        throw invalid_argument("it's not your turn, you can't trade");
    }
}

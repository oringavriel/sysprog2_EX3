# System programming- assignment 3
This project implements Catan game with 3 players ( board photo is added).
the project contains Makefile for running the program, a demo that preform a game round and a testing unit. 

## Vertex
This class represents a vertex of the board.
it has a static field for indexing the vertices- static size_t idCountVertex.
 It also has this private fields:
1.	string type- represent the type ot the vertex ( when a player builds a settlement or a city)
2.	Player *p = nullptr – represent the player which owns the vertex ( it first defines as nullptr).
3.	size_t index- index of the vertex
   
moreover, it has this public methods:
1.	Vertex()- constructor which initializes the index of the vertex
2.	Player *getPlayer()- getter for the player which owns the vertex
3.	void setPlayer(Player *p)- setter for the player to own the vertex
4.	string getType()- getter for the typr of the vertex
5.	void setType(string type)- setter to set the type of the vertex
6.	size_t getIndex()- getter for the index of the vertex
7.	 static void resetIdCount()- a method to reset the count of the vertices count


## Edge
This class represents an edge of the board. 
The class has a static field for indexing the edges- static size_t idCountEdge.
It also has this private fields:
1.	Vertex *v1- first vertex of the edge
2.	Vertex *v2- second  vertex of the edge
3.	Player *p = nullptr – represent the player which owns the edge ( it first defines as nullptr).
4.	size_t index- index of the edge

moreover, it has this public methods:
1.	Edge(Vertex *v1, Vertex *v2)- constructor to initialize the edge with its vertices and its index number.
2.	Vertex *getV1()- getter for the first vertex
3.	Vertex *getV2()- getter for the second vertex
4.	Player *getPlayer()- ()- getter for the player which owns the edge
5.	void setPlayer(Player *p)- setter for the player to own the edge
6.	  size_t getIndex()- getter for the index of the edge
7.	static void resetIdCount()- a method to reset the count of the edges count


## Tile
This class represents a tile of the board.
The class has a static field for indexing the tiles- static size_t idCountTile.
It also has this private fields:
1.	string type- type of the tile(mountains, pastures, forest, fields, hills, desert)
2.	string resource- type of the resource of the tile(mountains- iron, pastures- wool, forest- wood, fields- grain, hills- brick, desert- no resource "")
3.	 vector<Vertex *> vertices- a vector to store all 6 vertices of the tile
4.	size_t number- number on the tile ( for checking the result of the dice roll)
5.	size_t index- index of the tile
 
 the classes public methods are:
1.	Tile(string type, string resource, vector<Vertex *> vertices, size_t num)- constructor to initialize the tile
2.	~Tile()-  destructor
3.	string getType()- getter for the type of the tile
4.	string getResource()- getter for the resource of the tile
5.	vector<Vertex *> getVertices()- getter for the vertices vector of the tile
6.	size_t getNum()- getter for the number of the tile
7.	size_t getIndex()- getter for the index of the tile
8.	static void resetIdCount()- a method to reset the count of the tiles count


## Board
This class represents the board of the game with 3 private fields-
1.	vector<Vertex *> vertices;
2.	vector<Edge *> edges;
3.	vector<Tile *> tiles;

    and this public methods:
1.	void initVertices()- a method to initialize 54 vertices of the board
2.	void initEdges()- a method to initialize 72 edges of the board manually
3.	void initTiles()- a method to initialize 19 tiles of the board manually
4.	Board()- constructor to initialize the board using the three methods above
5.	~Board()- destructor
6.	vector<Vertex *> getVertices()- getter for the vertices of the board
7.	vector<Edge *> getEdges()- getter for the edges of the board
8.	vector<Tile *> getTiles()- getter for the tiles of the board
9.	bool isAvailableVertex(size_t v)- a method to check if the vertex is available( not owned by any player).
10.	void setPlayerAtVertex(size_t v, Player *p)- a method to set a player at a certain vertex
11.	void setTypeAtVertex(size_t v, string s)- a method to set the type of a certain vertex
12.	bool isAvailableEdge(size_t e)- a method to check if the edge is available( not owned by any player).
13.	void setPlayerAtEdge(size_t e, Player *p)- a method to set a player at a certain edge


## Cards
This class represents the bank cards pack by a map of card type and the number of cards of that type- map<string, int> cardsPack.
The class has this public methods:
1.	Cards()- constructor to initialize the map.
2.	vector<string> getCardTypes()- a method to get a vector of all card types
3.	map<string, int> getCardsPack()- a method to the bank cards pack
4.	void reduceCard(string str)- a method to reduce the card from the pac


## Player
a class to represent a player of the game .
private fields:
1.	string name- player's name
2.	int points- number of points
3.	map<string, int> resources- map of the player's resources and how many of each type
4.	map<string, int> cards- map of the player's cards and how many of each type

  	 public methods:
1.	void initCards() – initializes the cards of the player with all types as 0.
2.	void initResources()- initializes the resources of the player with all types as 0.
3.	Player()- empty constructor
4.	Player(string name)- conctructor
5.	int getPoints()- getter for the player's points number
6.	void addPoints(int num)- adds the player points in the amount given
7.	void printPoints()- prints the player's  number of points
8.	void printResourceMap()- prints the resource map
9.	void printCardMap()- prints the cards map
10.	string getName()- getter for the player's name
11.	map<string, int> getCards()- getter for the cards of the player
12.	void addCard(string card, int amount)- adds the card given in the amount provided
13.	void reduceCard(string card, int amount) - reduces the card given in the amount provided
14.	map<string, int> getResources()- getter for the resources of the player
15.	void reduceResource(string resource, int num) - reduces the resource given in the amount provided. If the amount given is bigger than the amount the player has it throws an exception.
16.	void addResource(string resource, int num)- )- adds the resource given in the amount provided. 
17.	int totalResourceCount()- returns the total count of the resources the player has.
18.	void placeFirstSettlemnts(size_t vertexNum1, size_t vertexNum2, Board *b)- a method to place the first settlements at the beginning of the game. It checks if the vertices are available( if not it throws exception) and then sets the player at that vertex and adds him the resource of the tile that the vertex is part of.
19.	void placeFirstRoads(size_t edgeNum1, size_t edgeNum2, Board *b)- a method to place the first roads at the beginning of the game. It checks if the edges are available and if they are near a settlement( if not it throws exception) . Then, if they are valid it sets the player at that edge.
20.	void addBiggestArmyCard(Cards &cardsPack)- the method adds the player the biggest army card if it's not in other player's posetion.
21.	void buyCard(Cards &cardsPack)- the method checks if the player has enough resources to but a card -else throws exception. If he has enough resources, it reduces the resources and randomly adds him a card. If the random card is a knight it checks if the player has 3 knights and if he has it calls the addBiggestArmyCard method.
22.	void useVictoryPointCard(Catan *catan)- checks if the player has victory point card, adds him a point and reduce the card from his pack and moves the turn to the next player. Else, throws an exception.
23.	void useYearOfPlentyCard(string card1, string card2, Catan *catan)- checks if the player has year of plenty card, adds him the two resources he chose and reduce the card from his pack and moves the turn to the next player. Else, throws an exception.
24.	void useMonopolyCard(vector<Player *> players, string Resource, Catan *catan) )- checks if the player has monopoly card, adds him the resource he chose from the other players and reduce the card from his pack and moves the turn to the next player. Else, throws an exception.
25.	void placeTwoRoadsBuildCard(size_t edgeNum1, size_t edgeNum2, Board *b)- the method first check if the edges are available. Then, It checks if they are near a settlement  or another road. If they are it sets the player to those roads, else, throws an exception.
26.	void useBuildRoadsCard(size_t VertexNum1, size_t VertexNum2, Board *b, Catan *catan)- checks if the player has build roads card, calls the placeTwoRoadsBuildCard method and reduce the card from his pack and moves the turn to the next player. Else, throws an exception.
27.	bool checkEdgeNearEdge(size_t edgeNum, Board *b)- a method to check if the edge has a near edge.
28.	void placeRoad(size_t edgeNum, Board *b)- first it checks if the player has enough resources to build the road. Then, It checks if the edge is available and if it's near a settlement  or another road. If not, it throws an exception. If it is, is reduces the resources and sets the player to the road.
29.	void placeSettlement(size_t vertexNum, Board *b )- first it checks if the player has enough resources to build the settlement. Then, It checks if the vertex is available, if it is near an edge and if it's at least 2 roads far from another settlement by the checkDistance method. If not, it throws an exception. If it is, is reduces the resources, adds a point to the player and sets the player and type to the vertex.
30.	void placeCity(size_t vertexNum, Board *b)- the method first checks if the player has enough resources to build the city and if he has a settlement in that vertex- if not it throws an exception. If yes, it reduces the resources, adds a point to the player and changes the vertex type.
31.	bool checkDistance(size_t vertexNum, Board *b)- a method to check if the vertex is at least 2 roads far from another settlement.
32.	void rollDice(Catan *c)- calls the rollDice method of catan.
33.	void returnHalf()-  a method that is called when the dice roll get 7. It reduces half of the player's resources ( to his choice).
34.	void tradeResources(Catan *catan, Player *other, string thisResource, int thisAmount, string otherResource, int otherAmount)- if it is the player's turn he can trade resources with another player by their terms.
35.	void tradeCards(Catan *catan, Player *other, string thisCard, int thisAmount, string otherCard, int otherAmount)- )- if it is the player's turn he can trade cards with another player by their terms.


## Catan
This class manage the Catan game.
Private fields:
1.	Board *board- the board game
2.	vector<Player *> players- vector of the players of the game
3.	Player *current- pointer to the current player (the player that it's his turn)
4.	Cards *cards- the bank cards pack

Public methods:
1.	void setCards()- creates the bank cards pack
2.	void setBoard()- creates the board game
3.	Catan(Player &p1, Player &p2, Player &p3)- constructor which initializes the three players of the game and also the board and cards by the methods aboce
4.	~Catan()- destructor
5.	Board *getBoard()- getter for the board of the game
6.	Cards *getCards()- getter for the bank cards pack of the game
7.	vector<Player *> getPlayers()-getter for the players of the game
8.	Player *getCurrent()- getter for the current player of the game
9.	void setCurrent(Player *p)- a method that sets the player as the currnet
10.	void chooseStartingPlayer()- a method that chooses the first player as thee starting player and initializes him as the current (players[0])
11.	void turnSwitch()- a method that moves the turn to the next player
12.	bool victory(Player *player)- the method checks if the player has more than 10 points. If it is it calls the printVictory method to print the winning player and returns true.
13.	void printVictory(Player *player)-prints the player that won the game
14.	void rollDice(Player *player)- the method rolls the dice randomly. If the number Is7 it calls the SevenDice method . for any number besides 9 ( which is the desert and has no resource) it calls the rollDiceResourceAdd to add each player the resources he should get.
15.	void rollDiceResourceAdd(int number)- ()- if the player got any number beside 9 and 7 in the roll dice, this function is called. It checks for all vertices of all tiles if one of the player owns them. Each player gets the resource of the tile. 
16.	void sevenDice()- if the player got 7 in the roll dice this function is called to make all players return half of their resources.


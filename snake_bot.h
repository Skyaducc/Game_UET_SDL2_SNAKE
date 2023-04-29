#ifndef SNAKE_BOT__H
#define SNAKE_BOT__H

#include <iostream>
#include <vector>
#include "Position.h"

using namespace std;

class Game;

struct SnakeBotNode
{
    Position position;
    SnakeBotNode *next;
    SnakeBotNode(Position p , SnakeBotNode* _next = nullptr) : position(p) , next(_next) {}
};

class SnakeBot
{
    SnakeBotNode *head , *tail;
    Game &game;
    int bird;
    int score;
    int startPosition;
    int finishPosition;
    vector<vector<int>> adj;
    vector<int> dist;
    vector<int> trace;
    vector<Position> traceSnakeBot;
    vector<Direction> directionSnakeBot;
    vector<Position> returnPosition;
public:
    SnakeBot(Game& _game , Position start , int _width , int _height);
    ~SnakeBot();

    void move(Position newPosition);
    bool checkPosition(Position pos);
    vector<Position> getPositions() const;
    vector<Position> getTraceSnakeBot() { return traceSnakeBot; }
    vector<Direction> getDirectionSnakeBot() { return directionSnakeBot; }
    void eatbird();
    void getPositionsTrace();
    void snakeBotRemoveTail();
    void slideTo(Position newPosition);
    void growAtFront(Position newPosition);
    int getVertice(int x , int y);
    bool checkInside(int x , int y);
    void bfs();
    void getTrace(int v);
};

#endif // SNAKE__H

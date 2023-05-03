#ifndef SNAKE__H
#define SNAKE__H

#include <vector>
#include "Position.h"

using namespace std;

class Game;

struct SnakeNode
{
    Position position;
    SnakeNode *next;
    SnakeNode(Position p , SnakeNode* _next = nullptr) : position(p) , next(_next) {}
};

class Snake
{
    SnakeNode *head , *tail;
    Game &game;
    int bird;
    int score;
public:
    Snake(Game& _game , Position start);
    ~Snake();

    void move(Direction direction);
    bool checkPosition(Position pos);
    vector<Position> getPositions() const;
    void eatbird();
    void snakeRemoveTail();
    void slideTo(Position newPosition);
    void growAtFront(Position newPosition);
    void addBird(int num) { bird = num; }
};

#endif // SNAKE__H

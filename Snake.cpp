#include "Snake.h"
#include "Game.h"
#include <iostream>

Snake::Snake(Game& _game , Position start)
    : head(new SnakeNode(start)) , tail(head) , game(_game) , bird(0)
{
//    cout << "check" << endl;
//    cout << "intilizeSnake" << game.width << " " << game.height << endl;
//    game.snakeMoveTo(start);
}

Snake::~Snake()
{
    for (SnakeNode* p = tail ; p != nullptr;)
    {
        SnakeNode* nextNode = p->next;
        delete p;
        p = nextNode;
    }
}

vector<Position> Snake::getPositions() const
{
    vector<Position> res;
    for(SnakeNode* p = tail ; p != nullptr; p = p -> next)
        res.push_back(p->position);
    return res;
}

void Snake::growAtFront(Position newPosition)
{
    head->next = new SnakeNode(newPosition);
    head = head->next;
}

void Snake::slideTo(Position newPosition)
{
    if(tail->next == nullptr)
        tail->position = newPosition;
    else
    {
        SnakeNode *oldTailNode = tail;

        tail = tail->next;
        oldTailNode->next = nullptr;

        oldTailNode->position = newPosition;
        head->next = oldTailNode;
        head = oldTailNode;
    }
}

void Snake::eatbird()
{
    bird++;
}

void Snake::move(Direction direction)
{
    Position newPosition = head->position.move(direction , game.width , game.height , game.isGameModeBasic());
//    cout << "move: " << newPosition.x << " " << newPosition.y << endl;
    game.snakeMoveTo(newPosition);
    if(game.isGameOver())   return;

    if(bird > 0)
    {
        bird--;
        growAtFront(newPosition);
    }
    else
    {
        game.snakeLeave(tail->position);
        slideTo(newPosition);
    }
}

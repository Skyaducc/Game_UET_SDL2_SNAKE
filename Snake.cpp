#include "Snake.h"
#include "Game.h"
#include <iostream>

Snake::Snake(Game& _game , Position start)
    : head(new SnakeNode(start)) , tail(head) , game(_game) , bird(0)
{
    cout << "Snake" << endl;
    bird = 5;
}

Snake::~Snake()
{
    cout << "~ snake" << endl;
    for (SnakeNode* p = tail ; p != nullptr;)
    {
        SnakeNode* nextNode = p->next;
        delete p;
        p = nextNode;
    }
}

vector<Position> Snake::getPositions() const
{
    cout << "getPositions" << endl;
    vector<Position> res;
    for(SnakeNode* p = tail ; p != nullptr; p = p -> next)
        res.push_back(p->position);
    return res;
}

void Snake::growAtFront(Position newPosition)
{
    cout << "growAtFront" << endl;
    head->next = new SnakeNode(newPosition , nullptr);
    head = head->next;
}

void Snake::snakeRemoveTail()
{
    game.snakeLeave(tail->position);
    if(tail->next == nullptr)
    {
        game.setGameOver();
        return;
    }
    tail = tail->next;
}

void Snake::slideTo(Position newPosition)
{
    cout << "slideTo" << endl;
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
    cout << "eatbird" << endl;
    bird++;
}

void Snake::move(Direction direction)
{
    cout << "move" << endl;
    Position newPosition = head->position.move(direction , game.width , game.height);
    game.snakeMoveTo(newPosition);
    if(game.isGameOver() || game.isGamePause())   return;

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

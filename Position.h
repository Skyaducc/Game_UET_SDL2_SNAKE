#ifndef POSITION__H
#define POSITION__H

#include <iostream>

using namespace std;

enum Direction
{
    UP = 0 , DOWN , LEFT , RIGHT
};

struct Position
{
    int x , y;
    Position(int _x = 0 , int _y = 0) : x(_x) , y(_y) {}
    Position move(Direction direction , int width , int height) const
    {
        switch(direction)
        {
            case UP:
            {
                int newY = (y == 0) ? height - 1 : y - 1;
                return Position(x , newY);
            }
            case DOWN:
            {
                int newY = (y == height - 1) ? 0 : y + 1;
                return Position(x , newY);
            }
            case LEFT:
            {
                int newX = (x == 0) ? width - 1 : x - 1;
                return Position(newX , y);
            }
            case RIGHT:
            {
                int newX = (x == width - 1) ? 0 : x + 1;
                return Position(newX , y);
            }
            default: throw std::invalid_argument("Unknown direction");
        }
    }
    bool isInsideBox(int left , int top , int width , int height) const
    {
//        cout << left << " " << top << " " << width << " " << height << " " << x << " " << y << endl;
        return x >= left && x < left + width && y >= top && y < top + height;
    }
    bool operator == (Position p) const
    {
        return x == p.x && y == p.y;
    }
};

#endif // POSITION__H

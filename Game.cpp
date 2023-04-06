#include <iostream>
#include "Game.h"

using namespace std;

Game::Game(int _width , int _height)
    : width(_width) , height(_height),
    squares(_height , vector<CellType>(_width , CELL_EMPTY)),
    snake(*this , Position(_width / 2 , _height / 2)),
    currentDirection(Direction::RIGHT),
    status(GAME_RUNNING),
    mode(GAME_MODE_ADVANCE),
    score(0) , numBird(0)
{
//    cout << "init game" << (int)(GAME_RUNNING) << " " << (int)(status) << endl;
    snakeMoveTo(Position(_width / 2 , _height / 2));
    addBird();
}

Game::~Game()
{
    //dtor
}

void Game::processUserInput(Direction direction)
{
    inputQueue.push(direction);
}

bool Game::canChange(Direction current , Direction next) const
{
    if(current == UP || current == DOWN)
        return next == LEFT || next == RIGHT;
    return next == UP || next == DOWN;
}

void Game::nextStep()
{
    while(!inputQueue.empty())
    {
        Direction next = inputQueue.front();
        inputQueue.pop();
        if(canChange(currentDirection , next))
        {
            currentDirection = next;
            break;
        }
    }
    snake.move(currentDirection);
}

void Game::snakeMoveTo(Position pos)
{
//    cout << "snakeMoveTo" << " ";
//    cout << (int)(status) << " ";
//    cout << pos.x << " " << pos.y << " ";
//    cout << (int)(getCellType(pos)) << " " << squares[pos.y][pos.x] << endl;
    switch(getCellType(pos))
    {
        case CELL_OFF_BOARD:
        {
            if(mode == GAME_MODE_BASIC)
            {
                status = GAME_OVER;
                break;
            }
        }
        case CELL_SNAKE: status = GAME_OVER; break;
        case CELL_BIRD:
        {
            for (int i=-1 ; i<=1 ; i++)
            {
                for (int j=-1 ; j<=1 ; j++)
                {
                    if(i == 0 && j == 0)    continue;
                    Position posTemp = {pos.x + i , pos.y + j};
                    if(getCellType(posTemp) == CELL_BIRD)  setCellType(posTemp , CELL_EMPTY);
                }
            }
            snake.eatbird();
            if(numBird % 5 == 4)    addBigBird();
            else addBird();
            if(numBird % 5 == 0 && numBird > 0) score += 5;
            else score += 1;
            numBird++;
        }
        default: setCellType(pos , CELL_SNAKE);
    }
}

void Game::snakeLeave(Position position)
{
    setCellType(position , CELL_EMPTY);
}

void Game::setCellType(Position pos , CellType cellType)
{
    if(pos.isInsideBox(0 , 0 , width , height)) squares[pos.y][pos.x] = cellType;
}

CellType Game::getCellType(Position pos) const
{
//    cout << "getCellType " << pos.isInsideBox(0 , 0 , width , height) << " " << width << " " << height << " " << pos.x << " " << pos.y  << endl;
    return pos.isInsideBox(0 , 0 , width , height) ? squares[pos.y][pos.x] : CELL_OFF_BOARD;
}

void Game::addBird()
{
//    cout << "addBird" << endl;
    do
    {
        Position p(rand() % width , rand() % height);
        if(getCellType(p) == CELL_EMPTY)
        {
            setCellType(p , CELL_BIRD);
            birdPosition = p;
            break;
        }
    }
    while(true);
}

void Game::addBigBird()
{
    do
    {
        Position p(rand() % (width - 2) , rand() % (height - 2));
//        cout << "addBigBird " << p.x << " " << p.y << " " << endl;
        Position p1(p.x + 1 , p.y);
        Position p2(p.x , p.y + 1);
        Position p3(p.x + 1 , p.y + 1);
//        cout << p1.x << " " << p1.y << endl << p2.x << " " << p2.y << endl << p3.x << " " << p3.y << endl;
        if(getCellType(p) == CELL_EMPTY
           && getCellType(p1) == CELL_EMPTY
           && getCellType(p2) == CELL_EMPTY
           && getCellType(p3) == CELL_EMPTY)
        {
            setCellType(p , CELL_BIRD);
            setCellType(p1 , CELL_BIRD);
            setCellType(p2 , CELL_BIRD);
            setCellType(p3 , CELL_BIRD);
            birdPosition = p;
            break;
        }
    }
    while(true);
}

vector<Position> Game::getbirdPosition() const
{
    vector<Position> res;
    res.push_back(birdPosition);
    if(numBird % 5 == 0 && numBird > 0) res.push_back({1 , 1});
    return res;
}

vector<Position> Game::getSnakePositions() const
{
    return snake.getPositions();
}

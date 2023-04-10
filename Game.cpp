#include <iostream>
#include "Game.h"

using namespace std;

Game::Game(int _width , int _height)
    : width(_width) , height(_height),
    squares(_height , vector<CellType>(_width , CELL_EMPTY)),
    hasWall(_height , vector<bool>(_width , false)),
    snake(*this , Position(0 , _height - 1)),
    snakeBot(*this , Position(_width - 1 , 0) , _width , _height),
    mode(GAME_MODE_ADVANCE),
    currentDirection(Direction::RIGHT),
    status(GAME_RUNNING),
    score(0) , numBird(0) , idSnakeBot(0),
    traceSnakeBot(_width * _height , Position(0 , 0))
{
    snakeMoveTo(Position(0 , _height - 1));
    addWall();
    addBird();
    snakeBot.getPositionsTrace();
    traceSnakeBot = snakeBot.getTraceSnakeBot();
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
//    cout << traceSnakeBot[idSnakeBot].x << " " << traceSnakeBot[idSnakeBot].y << endl;
    snakeBot.move(traceSnakeBot[idSnakeBot++]);
}

void Game::snakeMoveTo(Position pos)
{
//    cout << "snakeMoveTo: " << width << " " << height << endl;
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
        case CELL_WALL: status = GAME_OVER; break;
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
            snakeBot.getPositionsTrace();
            traceSnakeBot = snakeBot.getTraceSnakeBot();
            idSnakeBot = 0;
        }
        default: setCellType(pos , CELL_SNAKE);
    }
}

void Game::snakeBotMoveTo(Position pos)
{
    switch(getCellType(pos))
    {
        case CELL_BIRD:
        {
            for (int i=-1 ; i<=1 ; i++)
            {
                for (int j=-1 ; j<=1 ; j++)
                {
//                    if(i == 0 && j == 0)    continue;
                    Position posTemp = {pos.x + i , pos.y + j};
                    if(getCellType(posTemp) == CELL_BIRD)
                    {

                        setCellType(posTemp , CELL_EMPTY);
                    }
                }
            }
            snakeBot.eatbird();
            if(numBird % 5 == 4)    addBigBird();
            else addBird();
            if(numBird % 5 == 0 && numBird > 0) score += 5;
            else score += 1;
            numBird++;
            snakeBot.getPositionsTrace();
            traceSnakeBot = snakeBot.getTraceSnakeBot();
            idSnakeBot = 0;
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
//    cout << pos.x << " " << pos.y << " " << width << " " << height << endl;
//    cout << "getCellType " << pos.isInsideBox(0 , 0 , width , height) << " " << width << " " << height << " " << pos.x << " " << pos.y  << endl;
    return pos.isInsideBox(0 , 0 , width , height) ? squares[pos.y][pos.x] : CELL_OFF_BOARD;
}

void Game::addBird()
{
    cout << "addBird" << " ";
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
    cout << birdPosition.x << " " << birdPosition.y << endl;
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

void Game::addWall()
{
    int numWall = 0;
    while(numWall <= (width * height) / 5)
    {
        int x = rand() % (width - 2) + 1;
        int y = rand() % (height - 2) + 1;
        numWall++;
        if(!hasWall[y][x])
        {
            hasWall[y][x] = true;
            Position pos(x , y);
            setCellType(pos , CELL_WALL);
            numWall++;
        }
    }
}

vector<Position> Game::getWallPosition() const
{
    vector<Position> res;
    for (int x=0 ; x<width ; x++)
    {
        for (int y=0 ; y<height ; y++)
        {
            if(hasWall[y][x])
            {
                Position ans(x , y);
                res.push_back(ans);
            }
        }
    }
    return res;
}

void Game::runSnakeBot()
{
    snakeBot.getPositionsTrace();
}

vector<Position> Game::getSnakeBotPositions() const
{
    return snakeBot.getPositions();
}

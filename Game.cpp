#include <iostream>
#include "Game.h"
#include "constants.h"

using namespace std;

Game::Game(int _width , int _height)
    : width(_width) , height(_height),
    squares(_height , vector<CellType>(_width , CELL_EMPTY)),
    hasWall(_height , vector<bool>(_width , false)),
    snake(*this , Position(0 , _height - 1)),
    snakeBot(*this , Position(_width - 1 , 0) , _width , _height),
    status(GAME_RUNNING),
    score(0) , numBird(0),
    currentDirection(Direction::RIGHT),
    currentMap(MAPS::MAP_ICE),
    idSnakeBot(0),
    traceSnakeBot(_width * _height , Position(0 , 0)),
    directionSnakeBot(_width * _height , LEFT)
{
    cout << "Game" << endl;
    addMap();
//    addWall();
    addBird();
    snakeBot.getPositionsTrace();
    traceSnakeBot = snakeBot.getTraceSnakeBot();
    directionSnakeBot = snakeBot.getDirectionSnakeBot();
}

Game::~Game()
{
    cout << "~Game" << endl;
    //
}

void Game::playGameAgain()
{
    cout << "playGameAgain" << endl;
    for (int i=0 ; i<height ; i++)
    {
        for (int j=0 ; j<width ; j++)
        {
            squares[i][j] = CELL_EMPTY;
            hasWall[i][j] = false;
        }
    }
    currentDirection = Direction::RIGHT;
    currentMap = MAPS::MAP_ICE;
    status = GAME_RUNNING;
    score = numBird = idSnakeBot = 0;
    traceSnakeBot.clear();
    directionSnakeBot.clear();
//    snake.~Snake();
//    snakeBot.~SnakeBot();
    Snake snake(*this , Position(0 , height - 1));
    SnakeBot snakeBot(*this , Position(width - 1 , 0) , width , height);
    addMap();
    snakeMoveTo(Position(0 , height - 1));
    addBird();
    snakeBot.getPositionsTrace();
    traceSnakeBot = snakeBot.getTraceSnakeBot();
    directionSnakeBot = snakeBot.getDirectionSnakeBot();
}

void Game::addMap()
{
    cout << "addMap" << endl;
    int num = 0;
    for (int i=0 ; i<height ; i++)
    {
        for (int j=0 ; j<width ; j++)
        {
            if(mapField[num] == 1)     hasWall[i][j] = 1;
            squares[i][j] = (CellType)mapField[num++];
        }
    }
}

void Game::processUserInput(Direction direction)
{
    cout << "processUserInput" << endl;
    inputQueue.push(direction);
}

bool Game::canChange(Direction current , Direction next) const
{
    cout << "canChange" << endl;
    if(current == UP || current == DOWN)
        return next == LEFT || next == RIGHT;
    return next == UP || next == DOWN;
}

void Game::nextStep()
{
    cout << "nextStep" << endl;
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
    if(idSnakeBot >= (int)traceSnakeBot.size())
    {
        status = GAME_OVER;
        return;
    }
    snakeBot.move(traceSnakeBot[idSnakeBot++]);
//    cout << idSnakeBot << " " << traceSnakeBot[idSnakeBot].x << " " << traceSnakeBot[idSnakeBot].y << endl;
}

void Game::snakeMoveTo(Position pos)
{
    cout << "snakeMoveTo" << endl;
    switch(getCellType(pos))
    {
        case CELL_OFF_BOARD:
        {
            status = GAME_OVER;
            break;
        }
        case CELL_WALL:
        {
            cout << "CELL_WALL" << endl;
            status = GAME_OVER; break;
        }
        case CELL_SNAKE:
        {
            cout << "CELL_SNAKE" << endl;
            status = GAME_OVER; break;
        }
        case CELL_SNAKE_BOT:
        {
            cout << "CELL_SNAKE_BOT" << endl;
            status = GAME_OVER; break;
        }
        case CELL_BIRD:
        {
            for (int i=-1 ; i<=1 ; i++)
            {
                for (int j=-1 ; j<=1 ; j++)
                {
//                    if(i == 0 && j == 0)    continue;
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
            snakeBot.snakeBotRemoveTail();
            resetTraceSnakeBot();
        }
        default: setCellType(pos , CELL_SNAKE);
    }
}

bool Game::snakeBotMoveTo(Position pos)
{
    cout << "snakeBot MoveTo" << endl;
    bool checkIsCellBird = false;
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
            checkIsCellBird = true;
            snake.snakeRemoveTail();
        }
        default: setCellType(pos , CELL_SNAKE_BOT);
    }
    return checkIsCellBird;
}

void Game::resetTraceSnakeBot()
{
    cout << "resetTraceSnakeBot" << endl;
    snakeBot.getPositionsTrace();
    traceSnakeBot.clear();
    directionSnakeBot.clear();
    traceSnakeBot = snakeBot.getTraceSnakeBot();
    directionSnakeBot = snakeBot.getDirectionSnakeBot();
    idSnakeBot = 0;
}

void Game::snakeLeave(Position position)
{
    cout << "snakeLeave" << endl;
    setCellType(position , CELL_EMPTY);
}

void Game::setCellType(Position pos , CellType cellType)
{
    cout << "setCellType" << endl;
    if(pos.isInsideBox(0 , 0 , width , height)) squares[pos.y][pos.x] = cellType;
}

CellType Game::getCellType(Position pos) const
{
    cout << "getCellType" << endl;
    return pos.isInsideBox(0 , 0 , width , height) ? squares[pos.y][pos.x] : CELL_OFF_BOARD;
}

void Game::addBird()
{
    cout << "addBird" << endl;
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
//    cout << birdPosition.x << " " << birdPosition.y << endl;
}

void Game::addBigBird()
{
    cout << "addBigBird" << endl;
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
    cout << "getbirdPosition" << endl;
    vector<Position> res;
    res.push_back(birdPosition);
    if(numBird % 5 == 0 && numBird > 0) res.push_back({1 , 1});
    return res;
}

vector<Position> Game::getSnakePositions() const
{
    cout << "getSnakePositions" << endl;
    return snake.getPositions();
}

void Game::addWall()
{
    cout << "addWall" << endl;
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
    cout << "getWallPosition" << endl;
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
    cout << "runSnakeBot" << endl;
    snakeBot.getPositionsTrace();
}

vector<Position> Game::getSnakeBotPositions() const
{
    cout << "getSnakeBotPositions" << endl;
    return snakeBot.getPositions();
}

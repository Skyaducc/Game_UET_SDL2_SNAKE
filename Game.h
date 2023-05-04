#ifndef GAME__H
#define GAME__H

#include "Position.h"
#include "snake.h"
#include "snake_bot.h"
#include <bits/stdc++.h>

using namespace std;

enum GameStatus
{
    GAME_RUNNING,
    GAME_OVER,
    GAME_WIN,
    GAME_PAUSE
};

enum CellType
{
    CELL_EMPTY = 0,
    CELL_WALL,
    CELL_SNAKE,
    CELL_SNAKE_BOT,
    CELL_BIRD,
    CELL_B , CELL_O , CELL_N , CELL_U , CELL_S,
    CELL_OFF_BOARD
};

enum MAPS
{
    MAP_FOREST,
    MAP_FIELD,
    MAP_ICE,
    MAP_VOLCANO,
    MAP_NUM
};


class Game
{
    vector<vector<CellType>> squares;
    vector<vector<bool>> hasWall;
    Snake snake;
    SnakeBot snakeBot;
    GameStatus status;
    int score;
    int numBird;
    int heart;
    int countBird;
    bool hasBonus;
    queue<Direction> inputQueue;
    Direction currentDirection;
    MAPS currentMap;
    Position birdPosition;
    Position bonusPosition;
    char currentDigit;
    int idSnakeBot;
    vector<Position> traceSnakeBot;
    vector<Direction> directionSnakeBot;
    map<char , bool> bonus;
public:
    const int width;
    const int height;
    Game(int _width , int _height , int numMap);
    ~Game();
    void playGameAgain();

    bool isGameRunning() const { return status  == GAME_RUNNING; }
    bool isGameOver() const { return status == GAME_OVER; }
    bool isGamePause() const { return status == GAME_PAUSE; }
    void setGameOver()  { status = GAME_OVER; }
    void setGameWin() { status = GAME_WIN; }

    void continuePlay();
    bool checkMapIce() const { return currentMap == MAP_ICE; }
    bool checkMapForest() const { return currentMap == MAP_FOREST; }
    bool checkMapField() const { return currentMap == MAP_FIELD; }
    bool checkMapVolcano() const { return currentMap == MAP_VOLCANO; }
    void checkStatus() { cout << "Game status: " << (int)status << endl; }
    void processUserInput(Direction direction);
    void nextStep();
    const vector< vector<CellType> >& getSquares() const { return squares; }
    CellType getCellType(Position p) const;
    bool checkHasWall(int x , int y) const { return hasWall[x][y]; }

    vector<Position> getSnakePositions() const;
    vector<Position> getbirdPosition() const;
    vector<Position> getWallPosition() const;
    pair<Position , pair<int , bool>> getBonusPosition() const;

    Direction getDirection() const { return currentDirection; }
    int getScore() const { return score; }
    int getHeart() const { return heart; }
    bool canChange(Direction current , Direction next) const;

    void snakeMoveTo(Position position);
    void snakeLeave(Position position);

    void addBird();
    void addBigBird();
    void addWall();
    void addMap();
    void addBonus();
    void setCellType(Position pos, CellType cellType);

    void runSnakeBot();
    bool snakeBotMoveTo(Position pos);
    void resetTraceSnakeBot();
    Direction getDirectionBot() const { return directionSnakeBot[idSnakeBot]; }
    vector<Position> getSnakeBotPositions() const;
    map<char , bool> getBonus() const { return bonus; }
};

#endif // GAME__H

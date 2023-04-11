#ifndef GAME__H
#define GAME__H

#include "Position.h"
#include "snake.h"
#include "snake_bot.h"
#include <vector>
#include <queue>

using namespace std;

enum GameStatus
{
    GAME_RUNNING,
    GAME_OVER
};

enum CellType
{
    CELL_EMPTY = 0,
    CELL_SNAKE,
    CELL_BIRD,
    CELL_WALL,
    CELL_OFF_BOARD
};

enum GameMode
{
    GAME_MODE_BASIC = 0,
    GAME_MODE_ADVANCE
};

class Game
{
    vector<vector<CellType>> squares;
    vector<vector<bool>> hasWall;
    Snake snake;
    SnakeBot snakeBot;
    GameStatus status;
    GameMode mode;
    int score;
    int numBird;
    queue<Direction> inputQueue;
    Direction currentDirection;
    Position birdPosition;
    int idSnakeBot;
    vector<Position> traceSnakeBot;
public:
    const int width;
    const int height;
    Game(int _width , int _height);
    ~Game();

    bool isGameRunning() const { return status  == GAME_RUNNING; }
    bool isGameOver() const { return status == GAME_OVER; }
    bool isGameModeBasic() const { return mode == GAME_MODE_BASIC; }
    void checkStatus() { cout << "Game status: " << (int)status << endl; }
    void processUserInput(Direction direction);
    void nextStep();
    const vector< vector<CellType> >& getSquares() const { return squares; }
    CellType getCellType(Position p) const;
    bool checkHasWall(int x , int y) const { return hasWall[x][y]; }

    vector<Position> getSnakePositions() const;
    vector<Position> getbirdPosition() const;
    vector<Position> getWallPosition() const;

    int getScore() const { return score; }
    bool canChange(Direction current , Direction next) const;

    void snakeMoveTo(Position position);
    void snakeLeave(Position position);

    void addBird();
    void addBigBird();
    void addWall();
    void setCellType(Position pos, CellType cellType);

    void runSnakeBot();
    bool snakeBotMoveTo(Position pos);
    void resetTraceSnakeBot();
    vector<Position> getSnakeBotPositions() const;
};

#endif // GAME__H

#ifndef GAME__H
#define GAME__H

#include "Position.h"
#include "snake.h"
#include <vector>
#include <queue>

using namespace std;

enum GameStatus
{
    GAME_RUNNING = 1,
    GAME_OVER = 2
};

enum CellType
{
    CELL_EMPTY = 0,
    CELL_SNAKE,
    CELL_BIRD,
    CELL_OFF_BOARD
};

enum GameMode
{
    GAME_MODE_BASIC = 0,
    GAME_MODE_ADVANCE
};

class Game
{
    Position birdPosition;
    vector<vector<CellType>> squares;
    GameStatus status;
    Snake snake;
    GameMode mode;
    queue<Direction> inputQueue;
    Direction currentDirection;
    int score;
    int numBird;
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

    vector<Position> getSnakePositions() const;
    vector<Position> getbirdPosition() const;
    int getScore() const { return score; }
    bool canChange(Direction current , Direction next) const;

    void snakeMoveTo(Position position);
    void snakeLeave(Position position);
private:
    void addBird();
    void addBigBird();
    void setCellType(Position pos, CellType cellType);
};

#endif // GAME__H

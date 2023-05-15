#include <iostream>
#include "Game.h"
#include "constants.h"
#include "mixer.h"

using namespace std;

Game::Game(int _width , int _height , int numMap)
    : width(_width) , height(_height),
    squares(_height , vector<CellType>(_width , CELL_EMPTY)),
    hasWall(_height , vector<bool>(_width , false)),
    snake(*this , Position(0 , _height - 1)),
    snakeBot(*this , Position(_width - 1 , 0) , _width , _height),
    status(GAME_RUNNING),
    score(0) , numBird(0), heart(3), countBird(0) , hasBonus(true),
    currentDirection(Direction::RIGHT),
    currentMap(static_cast<MAPS>(numMap)),
    bonusPosition({-1 , -1}),
    currentDigit(' '),
    idSnakeBot(0),
    traceSnakeBot(_width * _height , Position(0 , 0)),
    directionSnakeBot(_width * _height , LEFT),
    bonus()
{
    cout << "Game" << endl;
    for (int i=0 ; i<5 ; i++)   bonus[BONUS[i]] = false;
    addMap();
    addBird();
    addBonus();
    snakeBot.getPositionsTrace();
    traceSnakeBot = snakeBot.getTraceSnakeBot();
    directionSnakeBot = snakeBot.getDirectionSnakeBot();
}

Game::~Game()
{
    cout << "~Game" << endl;
    //
}

void Game::addMap()
{
    cout << "addMap" << endl;
    int num = 0;
    for (int i=0 ; i<height ; i++)
    {
        for (int j=0 ; j<width ; j++)
        {
            if(currentMap == MAP_FOREST)
            {
                if(mapForest[num] == 1)     hasWall[i][j] = 1;
                squares[i][j] = (CellType)mapForest[num++];
            }
            if(currentMap == MAP_ICE)
            {
                if(mapIce[num] == 1)     hasWall[i][j] = 1;
                squares[i][j] = (CellType)mapIce[num++];
            }
            if(currentMap == MAP_VOLCANO)
            {
                if(mapVolcano[num] == 1)     hasWall[i][j] = 1;
                squares[i][j] = (CellType)mapVolcano[num++];
            }
            if(currentMap == MAP_FIELD)
            {
                if(mapField[num] == 1)     hasWall[i][j] = 1;
                squares[i][j] = (CellType)mapField[num++];
            }
        }
    }
}

void Game::addBonus()
{
    cout << "addBonus" << endl;
    setCellType(currentDirection , CELL_EMPTY);
    char notEatBonus[6];
    int cnt = 0;
    for (int i=0 ; i<5 ; i++)
    {
        if(!bonus[BONUS[i]])    notEatBonus[cnt++] = BONUS[i];
    }
    if(cnt == 0)
    {
        snake.addBird(3);
        heart = 3;
        loadWAV("sound_and_music/full_bonus.wav");
        for (int i=0 ; i<5 ; i++)
        {
            bonus[BONUS[i]] = false;
            notEatBonus[cnt++] = BONUS[i];
        }
    }
    int ran = rand() % cnt;
    cout << cnt << " " << ran << " " << notEatBonus[ran] << " ---------------------------------" << endl;
    do
    {
        Position p(rand() % width , rand() % height);
        if(getCellType(p) == CELL_EMPTY)
        {
            if(notEatBonus[ran] == 'b')
            {
                setCellType(p , CELL_B);
                bonusPosition = p;
                currentDigit = 'b';
            }
            if(notEatBonus[ran] == 'o')
            {
                setCellType(p , CELL_O);
                bonusPosition = p;
                currentDigit = 'o';
            }
            if(notEatBonus[ran] == 'n')
            {
                setCellType(p , CELL_N);
                bonusPosition = p;
                currentDigit = 'n';
            }
            if(notEatBonus[ran] == 'u')
            {
                setCellType(p , CELL_U);
                bonusPosition = p;
                currentDigit = 'u';
            }
            if(notEatBonus[ran] == 's')
            {
                setCellType(p , CELL_S);
                bonusPosition = p;
                currentDigit = 's';
            }
            break;
        }
    }
    while(true);
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
    cout << "---------------------------" << hasBonus << endl;
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
    if(countBird == 2 && hasBonus == false)
    {
        addBonus();
        countBird = 0;
        hasBonus = true;
    }
    snake.move(currentDirection);
//    cout << traceSnakeBot[idSnakeBot].x << " " << traceSnakeBot[idSnakeBot].y << endl;
    if(idSnakeBot >= (int)traceSnakeBot.size())
    {
        cout << "idsnakebot >= size trace snake bot" << " " << idSnakeBot << " " << (int)traceSnakeBot.size() << endl;
        status = GAME_OVER;
        loadWAV("sound_and_music/game_over.wav");
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
        case CELL_WALL:
        {
            cout << "CELL_WALL" << endl;
            loadWAV("sound_and_music/error.wav");
            if(heart >= 0) heart--;
            status = (!heart) ? GAME_OVER : GAME_PAUSE;
//            status = GAME_OVER;
            break;
        }
        case CELL_SNAKE:
        {
            cout << "CELL_SNAKE" << endl;
            loadWAV("sound_and_music/error.wav");
            if(heart >= 0) heart--;
            status = (!heart) ? GAME_OVER : GAME_PAUSE;
//            status = GAME_OVER;
            break;
        }
        case CELL_SNAKE_BOT:
        {
            cout << "CELL_SNAKE_BOT" << endl;
            loadWAV("sound_and_music/error.wav");
            if(heart >= 0) heart--;
            status = (!heart) ? GAME_OVER : GAME_PAUSE;
//            status = GAME_OVER;
            break;
        }
        case CELL_BIRD:
        {
            cout << "CELL_BIRD"  << endl;
            loadWAV("sound_and_music/eat_bird.wav");
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
            if(hasBonus == false) countBird++;
            snakeBot.snakeBotRemoveTail();
            resetTraceSnakeBot();
            break;
        }
        case CELL_B:
        {
            cout << "                           CELL_B" << endl;
            loadWAV("sound_and_music/eat_bonus.wav");
            bonus['b'] = true;
            hasBonus = false;
            break;
        }
        case CELL_O:
        {
            cout << "                                 CELL_O" << endl;
            loadWAV("sound_and_music/eat_bonus.wav");
            bonus['o'] = true;
            hasBonus = false;
            break;
        }
        case CELL_N:
        {
            cout << "                        CELL_N" << endl;
            loadWAV("sound_and_music/eat_bonus.wav");
            bonus['n'] = true;
            hasBonus = false;
            break;
        }
        case CELL_U:
        {
            cout << "                     CELL_U" << endl;
            loadWAV("sound_and_music/eat_bonus.wav");
            bonus['u'] = true;
            hasBonus = false;
            break;
        }
        case CELL_S:
        {
            cout << "                             CELL_S" << endl;
            loadWAV("sound_and_music/eat_bonus.wav");
            bonus['s'] = true;
            hasBonus = false;
            break;
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
            cout << "CELL_BIRD" << endl;
            loadWAV("sound_and_music/eat_bird.wav");
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
            if(numBird % 5 == 4)
            {
                addBigBird();
                numBird += 2;
            }
            else
            {
                addBird();
                numBird++;
            }
            if(hasBonus == false) countBird++;
            checkIsCellBird = true;
            snake.snakeRemoveTail();
            break;
        }
        case CELL_B:
        {
            hasBonus = false;
            loadWAV("sound_and_music/eat_bonus.wav");
            break;
        }
        case CELL_O:
        {
            hasBonus = false;
            loadWAV("sound_and_music/eat_bonus.wav");
            break;
        }
        case CELL_N:
        {
            hasBonus = false;
            loadWAV("sound_and_music/eat_bonus.wav");
            break;
        }
        case CELL_U:
        {
            hasBonus = false;
            loadWAV("sound_and_music/eat_bonus.wav");
            break;
        }
        case CELL_S:
        {
            hasBonus = false;
            loadWAV("sound_and_music/eat_bonus.wav");
            break;
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
        if((p.x == 0 && p.y == height) || (p.x == width || p.y == 0))    continue;
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

pair<Position , pair<int , bool>> Game::getBonusPosition() const
{
    pair<Position , pair<int , bool>> res = {{0 , 0} , {0 , 0}};
    res.first = bonusPosition;
    for (int i=0 ; i<5 ; i++)
    {
        if(BONUS[i] == currentDigit) res.second.first = i;
    }
    res.second.second = hasBonus;
    return res;
}

void Game::continuePlay()
{
    cout << "continuePlay" << endl;
    status = GAME_RUNNING;
}

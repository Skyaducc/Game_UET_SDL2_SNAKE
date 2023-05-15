#include "snake_bot.h"
#include "Game.h"
#include "constants.h"
#include "Position.h"
#include <iostream>
#include <algorithm>

SnakeBot::SnakeBot(Game& _game , Position start , int _width , int _height)
    : head(new SnakeBotNode(start)) , tail(head) , game(_game) , bird(0), score(0),
    startPosition(0) , finishPosition(0),
    adj(_height * _width , vector<int>(4 , 0)),
    dist(_height * _width , 0),
    trace(_height * _width , 0),
    traceSnakeBot(_width * _height , Position(0 , 0)),
    directionSnakeBot(_width * _height , LEFT),
    returnPosition(_width * _height , Position(0 , 0))
{
    cout << "SnakeBot" << endl;
    bird = 5;
    startPosition = getVertice(start.x , start.y);
}

SnakeBot::~SnakeBot()
{
    cout << "~ snake bot" << endl;
    for (SnakeBotNode* p = tail ; p != nullptr;)
    {
        SnakeBotNode* nextNode = p->next;
        delete p;
        p = nextNode;
    }
}

vector<Position> SnakeBot::getPositions() const
{
    cout << "Snakebot getPositions" << endl;
    vector<Position> res;
    for(SnakeBotNode* p = tail ; p != nullptr; p = p -> next)
        res.push_back(p->position);
    return res;
}

void SnakeBot::growAtFront(Position newPosition)
{
    cout << "SnakeBot growAtFront" <<endl;
    head->next = new SnakeBotNode(newPosition);
    head = head->next;
}

void SnakeBot::snakeBotRemoveTail()
{
    game.snakeLeave(tail->position);
    if(tail->next == nullptr)
    {
        game.setGameWin();
        return;
    }
    tail = tail->next;
}

void SnakeBot::slideTo(Position newPosition)
{
    cout << "SnakeBot slideTo" << endl;
    if(tail->next == nullptr)
        tail->position = newPosition;
    else
    {
        SnakeBotNode *oldTailNode = tail;

        tail = tail->next;
        oldTailNode->next = nullptr;

        oldTailNode->position = newPosition;
        head->next = oldTailNode;
        head = oldTailNode;
    }
}

void SnakeBot::eatbird()
{
    cout << "SnakeBot eatbird" << endl;
    bird++;
}

void SnakeBot::move(Position newPosition)
{
    cout << "SnakeBot move" << endl;
    bool checkIsCellBird = game.snakeBotMoveTo(newPosition);
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
    if(checkIsCellBird) game.resetTraceSnakeBot();
}
int SnakeBot::getVertice(int x , int y)
{
//    cout << "SnakeBot getVertice" << endl;
	return game.width * y + x;
}

bool SnakeBot::checkInside(int x , int y)
{
//    cout << "SnakeBot checkInside" << endl;
	return 0 <= x && 0 <= y && x < game.width && y < game.height;
}

void SnakeBot::getTrace(int v)
{
//    cout << "SnakeBotgetTrace" << endl;
	if(v == startPosition)	return;
	traceSnakeBot.push_back(returnPosition[v]);
	int u = trace[v];
	getTrace(u);
}

void SnakeBot::bfs()
{
    cout << "SnakeBot bfs" << endl;
	queue<int> qu;
	qu.push(startPosition);
	for (int i=0 ; i<game.width * game.height ; i++)	dist[i] = trace[i] = 1e9;
	dist[startPosition] = 0;
	while(qu.size())
	{
		int u = qu.front();
		qu.pop();
		for (int v : adj[u])
		{
			if(dist[v] > dist[u] + 1)
			{
				dist[v] = dist[u] + 1;
				trace[v] = u;
				qu.push(v);
			}
		}
	}
}

void SnakeBot::getPositionsTrace()
{
    cout << "SnakeBot getPositionsTrace" << endl;
    SnakeBotNode* p = head;
    startPosition = getVertice(p->position.x , p->position.y);
//    cout << p->position.x << " " << p->position.y << endl;
    vector<vector<CellType>> squares = game.getSquares();
//    cout << game.height << " " << game.width << endl;
//    for (int y=0 ; y<game.height ; y++)
//    {
//        for (int x=0 ; x<game.width ; x++)
//        {
//            cout << squares[y][x] << " ";
//        }
//        cout << endl;
//    }
    for (int i=0 ; i<game.height * game.width ; i++)    adj[i].clear();
    traceSnakeBot.clear();
    returnPosition.clear();
	for (int y=0 ; y<game.height ; y++)
	{
		for (int x=0 ; x<game.width ; x++)
		{
		    returnPosition[getVertice(x , y)] = {x , y};
		    if(squares[y][x] == CELL_BIRD) finishPosition = getVertice(x , y);
			if(squares[y][x] == CELL_WALL)	continue;
			if(squares[y][x] == CELL_SNAKE_BOT) continue;
			for (int k=0 ; k<=3 ; k++)
			{
				int newX = x + dx[k];
				int newY = y + dy[k];
				if(checkInside(newX , newY) && (squares[newY][newX] != CELL_WALL && squares[newY][newX] != CELL_SNAKE_BOT))
				{
//				    cout << x << " " << y << " " << newX << " " << newY << endl;
					int u = getVertice(x , y);
					int v = getVertice(newX , newY);
					adj[u].push_back(v);
					adj[v].push_back(u);
				}
			}
		}
	}
	for (int k=0 ; k<=3 ; k++)
    {
        int newX = p->position.x + dx[k];
        int newY = p->position.y + dy[k];
        if(checkInside(newX , newY) && (squares[newY][newX] != CELL_WALL && squares[newY][newX] != CELL_SNAKE_BOT))
        {
//            cout << p->position.x << " " << p->position.y << " " << newX << " " << newY << endl;
            int u = getVertice(p->position.x , p->position.y);
            int v = getVertice(newX , newY);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
	bfs();
	if(dist[finishPosition] == 1e9)
    {
        cout << "No Trace Snake Bot" << endl;
        return;
    }
	traceSnakeBot.clear();
	getTrace(finishPosition);
	reverse(traceSnakeBot.begin() , traceSnakeBot.end());
    Direction oldDirection = (directionSnakeBot.size()) ? directionSnakeBot.back() : LEFT;
    directionSnakeBot.clear();
    directionSnakeBot.push_back(oldDirection);
	for (int i=1 ; i<(int)traceSnakeBot.size() ; i++)
    {
        if(traceSnakeBot[i].x == traceSnakeBot[i-1].x)
        {
            if(traceSnakeBot[i].y == traceSnakeBot[i-1].y - 1) directionSnakeBot.push_back(UP);
            else directionSnakeBot.push_back(DOWN);
        }
        else
        {
            if(traceSnakeBot[i].x == traceSnakeBot[i-1].x - 1) directionSnakeBot.push_back(LEFT);
            else directionSnakeBot.push_back(RIGHT);
        }
    }
//	cout << "startPosion & finishPosition" << returnPosition[startPosition].x << " " << returnPosition[startPosition].y << " ";
//	cout << returnPosition[finishPosition].x << " " << returnPosition[finishPosition].y << endl;
//    for (int i=0 ; i<(int)traceSnakeBot.size() ; i++)   cout << traceSnakeBot[i].x << " " << traceSnakeBot[i].y << " " << (int)directionSnakeBot[i] << endl;
}

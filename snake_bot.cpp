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
    returnPosition(_width * _height , Position(0 , 0))
{
    startPosition = getVertice(start.x , start.y);
}

SnakeBot::~SnakeBot()
{
    for (SnakeBotNode* p = tail ; p != nullptr;)
    {
        SnakeBotNode* nextNode = p->next;
        delete p;
        p = nextNode;
    }
}

vector<Position> SnakeBot::getPositions() const
{
    vector<Position> res;
    for(SnakeBotNode* p = tail ; p != nullptr; p = p -> next)
        res.push_back(p->position);
    return res;
}

void SnakeBot::growAtFront(Position newPosition)
{
    head->next = new SnakeBotNode(newPosition);
    head = head->next;
}

void SnakeBot::slideTo(Position newPosition)
{
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
    bird++;
}

void SnakeBot::move(Position newPosition)
{
//    cout << "move: " << newPosition.x << " " << newPosition.y << endl;
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
	return game.width * y + x;
}

bool SnakeBot::checkInside(int x , int y)
{
	return 0 <= x && 0 <= y && x < game.width && y < game.height;
}
int cnt = 0;
void SnakeBot::getTrace(int v)
{
    cnt++;
	if(v == startPosition)	return;
	traceSnakeBot.push_back(returnPosition[v]);
	int u = trace[v];
	getTrace(u);
}

void SnakeBot::bfs()
{
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
    cout << "getPositionsTrace" << endl;
    SnakeBotNode* p = head;
    int headX = p->position.x;
    int headY = p->position.y;
    startPosition = getVertice(headX , headY);
//    cout << headX << " " << headY << endl;
    vector<vector<CellType>> squares = game.getSquares();
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
			if(squares[y][x] == CELL_SNAKE && (x != headX || y != headY)) continue;
			for (int k=0 ; k<3 ; k++)
			{
				int newX = x + dx[k];
				int newY = y + dy[k];
				if(checkInside(newX , newY) && (squares[newY][newX] == CELL_BIRD || squares[newY][newX] == CELL_EMPTY))
				{
//				    cout << x << " " << y << " " << newX << " " << newY << " " << (int)squares[y][x] << " " << (int)squares[newY][newX] << headX <<" " << headY << endl;
					int u = getVertice(x , y);
					int v = getVertice(newX , newY);
					adj[u].push_back(v);
					adj[v].push_back(u);
				}
			}
		}
	}
	bfs();
	traceSnakeBot.clear();
	getTrace(finishPosition);
	reverse(traceSnakeBot.begin() , traceSnakeBot.end());
//	cout << "startPosion & finishPosition" << returnPosition[startPosition].x << " " << returnPosition[startPosition].y << " ";
//	cout << returnPosition[finishPosition].x << " " << returnPosition[finishPosition].y << endl;
//    for (auto p : traceSnakeBot)    cout << p.x << " " << p.y << endl;
}


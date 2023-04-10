#include <bits/stdc++.h>
#define endl '\n'
#define MASK(i) (1LL << (i))
#define BIT(x, i) (((x) >> (i)) & 1)
#define SET_ON(x, i) ((x) | MASK(i))
#define SET_OFF(x, i) ((x) & ~MASK(i))
#define reset(arr) memset((arr) , 0 , sizeof(arr))
#define debug(x) cout << x << endl; 
using namespace std;
int height , width , sta , fns;
int dx[] = {0 , 0 , -1 , 1};
int dy[] = {-1 , 1 , 0 , 0};
vector<int> adj[1000];
int dist[1001] , trace[1001];
vector<pair<int , int> > res;
pair<int , int> getPair[1001];
bool Inside(int x , int y)
{
	return 0 <= x && 0 <= y && x < width && y < height;
}
int Get(int x , int y)
{
	return width * y + x;
}
void bfs(int sta)
{
	queue<int> qu;
	qu.push(sta);
	for (int i=0 ; i<width * height ; i++)	dist[i] = 1e9;
	dist[sta] = 0;
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
void getTrace(int v)
{
	if(v == sta)	return;
	res.push_back(getPair[v]);
	int u = trace[v];
	getTrace(u);
}
void solve()
{
	cin >> height >> width;
	vector<vector<int>> Map(height , vector<int>(width , 0));
	for (int y=0 ; y<height ; y++)
	{
		for (int x=0 ; x<width ; x++)
		{
			int val; cin >> val;
			if(val == 2)	sta = Get(x , y);
			if(val == 3)	fns = Get(x , y);
			getPair[Get(x , y)] = {x , y};
			Map[y][x] = val;
		}
	}
	for (int y=0 ; y<height ; y++)
	{
		for (int x=0 ; x<width ; x++)
		{
			if(Map[y][x] == 1)	continue;
			for (int k=0 ; k<3 ; k++)
			{
				int newX = x + dx[k];
				int newY = y + dy[k];
				if(Inside(newX , newY) && (Map[newY][newX] == 0 || Map[newY][newX] == 2 || Map[newY][newX] == 3))
				{
					int u = Get(x , y); 
					int v = Get(newX , newY);
					adj[u].push_back(v);
					adj[v].push_back(u);
				}
			}
		}
	}
	bfs(sta);
	getTrace(fns);
	reverse(res.begin() , res.end());
	for (auto p : res)
	{
		cout << p.first << " " << p.second << endl;
	}
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("A.INP" , "r" , stdin);
    freopen("A.OUT" , "w" , stdout);
    solve();
    return 0;
}
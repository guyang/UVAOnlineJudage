#include <iostream>
using namespace std;

typedef struct
{
	int cost;
	int value;
	int type;
} bumperorwall;

bumperorwall grid[53][53];
int m, n, wc, p;

enum { dr=0, du, dl, dd };
enum { none = 0, wall, bumper };
bool next(int&, int&, int&, int&, int&);

int main()
{
	cin >> m >> n >> wc >> p;

	for(int i = 1 ; i<=m; i++)
		for(int j = 1; j <=n; j++)
		{
			if(i == 1 || j == 1 || i == m || j == n)
			{
				grid[i][j].cost = wc;
				grid[i][j].value = 0; // for walls, no gain
				grid[i][j].type = wall;
			}
		}

	int x, y, v, c;
	while(p-- > 0 && cin >> x >> y >> v >> c)
	{
		grid[x][y].cost = c;
		grid[x][y].value = v;
		grid[x][y].type = bumper;
	}

	// reuse v: direction, c: lifetime
	int accgain = 0;
	while(cin >> x >> y >> v >> c)
	{
		int gain = 0;
		while(next(x, y, v, c, gain));
		cout << gain << endl;
		accgain += gain;
	}

	cout << accgain << endl;

	return 0;
}

void move(int &x, int &y, const int &dir)
{
	switch(dir)
	{
	case dr:
		x++;
		break;
	case du:
		y++;
		break;
	case dl:
		x--;
		break;
	default:
		y--;
		break;
	}
}

bool next(int &x, int &y, int &dir, int &l, int &gain)
{
	if (l <= 0) return false;

	switch (grid[x][y].type)
	{
	default:
		break;
	case bumper:
		gain += grid[x][y].value;
		// fall through
	case wall:
		l -= grid[x][y].cost;
		// move back without reducing life time
		move(x, y, (dir + 2 ) % 4);
		// turn right
		dir = (dir + 3) % 4;
		return true;
	}

	move(x, y, dir);
	l -= 1;

	return true;
}
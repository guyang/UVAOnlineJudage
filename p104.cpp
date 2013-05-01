#include <iostream>
#include <memory.h>
#include <stack>
using namespace std;

/*
P104

Assume we know d(s, i, j), i.e, from i to j in s steps
d(s+1, i, j) = max{ d(s, i, 1) * d(1, 1, j), d(s, i, 2) * d(1, 2, j), ... d(s, i, n) * d(1, n, j) }

Next vertex could be any one of the n vertexes
*/
int main()
{
	double profits[21][20][20];
	int path[21][20][20];
	int n;

	while(cin >> n)
	{
		memset(path, 0, sizeof(path));
		memset(profits, 0, sizeof(profits));
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
			{
				if (i == j)
				{
					profits[0][i][j] = 1.0;
					continue;
				}

				cin >> profits[0][i][j];
			}

		int s, v;
		for(s = 1; s <=n; s++)
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					for(int k = 0; k < n; k++)
					{
						double tmp = profits[s-1][i][k] * profits[0][k][j];
						if (profits[s][i][j] < tmp)
						{
							profits[s][i][j] = tmp;
							path[s][i][j] = k;

							if (tmp > 1.01 && i == j)
							{
								v = i;
								goto found;
							}
						}
					}

found:
		// Did we find a solution?
		if (s > n)
			cout << "no arbitrage sequence exists";
		else
		{
			stack<int> ss;
			ss.push(v);
			for(int l = s, p = v; l > 0; l--)
			{
				p = path[l][v][p];
				ss.push(p);
			}

			cout << v + 1;
			while(!ss.empty())
			{
				cout << " " << ss.top() + 1;
				ss.pop();
			}
		}

		cout << endl;
	}

	return 0;
}
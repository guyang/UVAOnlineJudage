#include <iostream>
#include <cstring>
#include <climits>
using namespace std;

/*
4
-1 -2 -3 -4
-5 -6 -7 -8
-9 -10 -11 -12
-13 -14 -15 -16
5
1 -61 5126 612 6
41 6 7 2 -7 1
73 -62 678 1 7
-616136 61 -83 724 -151
6247 872 2517 8135
4
0 -2 -7 0 
9 2 -6 2
-4 1 -4  1
-1 8  0 -2

-1
18589
15
*/

#define MAX 101

int main()
{
	int r[MAX][MAX] = {0};
	int cpf[MAX][MAX] = {0};

	int n, max;
	while(cin >> n)
	{
		max = INT_MIN;
		memset(r, 0, sizeof(r));
		memset(cpf, 0, sizeof(cpf));
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				cin >> r[i][j];

		// calc column prefix
		for(int j = 0; j < n; j++) cpf[0][j] = r[0][j]; // special handling for the 1st row
		for(int i = 1; i < n; i++) // handle rest of rows
			for(int j = 0; j < n; j++)
				cpf[i][j] += cpf[i-1][j] + r[i][j];

		// enumerate all [a,b]
		for(int i = 0; i < n; i++)
			for(int j = i; j < n; j++)
			{
				int tmpmax = 0;
				for(int k = 0; k < n; k++)
				{
					tmpmax += cpf[j][k] - cpf[i][k] + r[i][k];
					if (tmpmax > max)
						max = tmpmax;
					
					if (tmpmax < 0)
						tmpmax = 0;

				}
			}

		cout << max << endl;
	}

	return 0;
}
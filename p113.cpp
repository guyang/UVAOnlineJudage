#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

double nthroot(double q, int);

int main()
{
	double q;
	int n;
	while(cin >> n >> q)
		printf("%0.lf\n", nthroot(q, n));

	return 0;
}

double nthroot(double q, int n)
{
	return exp(log(q)/n);
}
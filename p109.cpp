#include <iostream>
#include <stack>
#include <cassert>
using namespace std;

typedef struct point
{
	int x;
	int y;

	point(int x = 0, int y = 0) : x(x), y(y) { }
} *ppoint;

point operator-(const point& p1, const point& p2)
{
	return point(p1.x - p2.x, p1.y - p2.y);
}

point kingdom[101];

double polygonarea(ppoint gp, int cp);

enum { collinear, dirleft, dirright };
int direction(point p, point p1, point p2); // true if p-p1 to p-p2 turns counter clockwise
void convexhull(ppoint p, int &n);
void _convexhullunit();

int main()
{
	_convexhullunit();
	return 0;
}

double polygonarea(ppoint gp, int cp)
{
	if (cp < 3)
		return 0.0;

	double sum = 0.0;

	for(int i = 1; i <= cp; i++)
	{
		point p1 = gp[i-1];
		point p2 = gp[i%cp];
		sum += p1.x * p2.y - p2.x * p1.y;
	}

	return sum;
}

int direction(point p, point p1, point p2)
{
	point p3[3] = { p, p1, p2 };

	double area = polygonarea(p3, 3);

	if(area == 0.0)
		return collinear;
	else if (area > 0)
		return dirleft;
	else
		return dirright;
}

/*
test data
8 7 7 7 -7 -7 -7 -7 7 9 0 -9 0 0 9 0 -9

8 (0, -9) (7, -7) (9, 0) (7, 7) (0, 9) (-7, 7) (-9, 0) (-7, -7)

*/
void _convexhullunit()
{
	point test[8] = {point(7,7), point(7,-7), point(-7,-7), point(-7,7), point(9,0), point(-9,0), point(0,9), point(0,-9)};
	int n = 8;
	convexhull(test, n);
	assert(n == 8);
}

void convexhull(ppoint p, int &n)
{
	if (n <= 3)
		return;

	int iMin = 0;
	ppoint pMin = p + iMin;
	for(int i = 1; i < n; i++)
	{
		if (p[i].y < pMin->y ||
			(p[i].y == pMin->y && p[i].x < pMin->x))
		{
			iMin = i;
			pMin = p + i;
		}
	}

	stack<ppoint> poly;
	poly.push(pMin);
	poly.push(p + ((iMin + 1) % n));

	bool done = false;

	while(true)
	{
		for(int j = 0; j < n; j++)
		{
			ppoint pp2 = poly.top();
			poly.pop();
			ppoint pp1 = poly.top();

			if (pp1 == p + j || pp2 == p + j)
			{
				poly.push(pp2);
				continue;
			}
			else
			{
				int dir = direction(*pp1, *pp2, p[j]);
				if(dir == dirleft || dir == collinear)
				{
					if (p + j == pMin)
					{
						done = true;
						break;
					}
					else
					{
						poly.push(p + j);
					}
				}
				else
				{
					poly.push(pp2); // push it back
					poly.push(p + j);
				}
			}
		}

		if (done)
			break;
	}

	assert(poly.size() <= n);

	// Fix kingdom into convex poly
	n = poly.size();
	for(int i = n; i > 0; i--)
	{
		p[i-1] = *poly.top();
		poly.pop();
	}
}
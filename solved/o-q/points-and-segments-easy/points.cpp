#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 100


struct Point {
	int i, x, c;
	Point() {}
	Point(int I, int X): i(I), x(X) {}
};


int n, m;
Point pts[MAXN];


bool cmp_by_x(const Point &a, const Point &b) { return a.x < b.x; }
bool cmp_by_i(const Point &a, const Point &b) { return a.i < b.i; }

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		pts[i] = Point(i, x);
	}
	for (int i = 0; i < m; ++i) scanf("%*d%*d");

	sort(pts, pts + n, cmp_by_x);

	int color = 0;
	for (int i = 0, x = 1; i < n; ++i, color += x, x *= -1)
		pts[i].c = color;

	sort(pts, pts + n, cmp_by_i);

	for (int i = 0; i < n; ++i) {
		if (i > 0) putchar(' ');
		printf("%d", pts[i].c);
	}
	putchar('\n');

	return 0;
}

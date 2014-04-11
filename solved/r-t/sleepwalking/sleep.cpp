#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 100


typedef int GeomT;

#define eqz(x)   ((x) == 0)
#define cmp(a,b) ((a) - (b))


//
// 2D Data Types
//
struct Point {
	GeomT x, y;
	Point() {}
	Point(GeomT X, GeomT Y) : x(X), y(Y) {}

	void dbg() const { printf("P(%d, %d)", x, y); }

	bool is_collinear(const Point &a, const Point &b) const {
		return eqz(cross(a, b));
	}

	bool in_box(const Point &a, const Point &b) const {
		GeomT lox = min(a.x, b.x), hix = max(a.x, b.x);
		GeomT loy = min(a.y, b.y), hiy = max(a.y, b.y);
		return cmp(lox, x) <= 0 && cmp(x, hix) <= 0 &&
			cmp(loy, y) <= 0 && cmp(y, hiy) <= 0;
	}

	// cross product magnitude of {a}x{b}, relative to {this}
	GeomT cross(const Point &a, const Point &b) const {
		return (a.x-x)*(b.y-y) - (a.y-y)*(b.x-x);
	}
};

bool is_inside_poly(const Point &p, Point *poly, int n)
{
	int cnt = 0;
	for (int u = n - 1, v = 0; v < n; u = v++) {
		Point *a = &poly[u];
		Point *b = &poly[v];

		if (p.is_collinear(*a, *b) && p.in_box(*a, *b)) return true;
		if (p.cross(*a, *b) < 0) swap(a, b);
		if (a->y >= p.y && b->y < p.y) ++cnt;
	}
	return cnt % 2 != 0;
}


Point pts[MAXN];
int n, q;


int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
			scanf("%d%d", &pts[i].x, &pts[i].y);

		printf("Case %d:\n", ++ncase);

		scanf("%d", &q);
		while (q--) {
			int x, y;
			scanf("%d%d", &x, &y);
			if (is_inside_poly(Point(x, y), pts, n))
				puts("Yes");
			else
				puts("No");
		}
	}

	return 0;
}

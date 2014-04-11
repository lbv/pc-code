#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;


#if 0
#define MAXT 10
#define MAXN 100
#define MAXQ 300
#define MINX -10000
#define MAXX 10000
#define NCRIT 2
#endif

#if 1
#define MAXT 10
#define MAXN 11
#define MAXQ 30
#define MINX -100
#define MAXX 100
#define NCRIT 2
#define NL 1
#endif


const int RangeX = MAXX - MINX + 1;
const double EPS = 1e-9;

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


typedef double GeomT;

bool eqz(GeomT x) { return fabs(x) < EPS; }
GeomT sanitize(GeomT x) { return eqz(x) ? 0.0 : x; }
int cmp(GeomT a, GeomT b)
{
	GeomT s; if (eqz(s = a-b)) return 0;
	return s < 0 ? -1 : 1;
}

struct Point {
	GeomT x, y, a;
	Point() {}
	Point(GeomT X, GeomT Y) : x(X), y(Y) { a = atan2(y, x); }

	bool operator<(const Point &p) const {
		return cmp(a, p.a) < 0;
	}
};

int T;


void test_case(bool crit = false)
{
	int n = crit ? MAXN : rand() % (MAXN - 2) + 3;

#if NL
	puts("");
#endif
	printf("%d\n", n);
	set<Point> pts;
	for (int i = 0; i < n; ++i) {
		Point p;
		do {
			int x = rand() % RangeX + MINX;
			int y = rand() % RangeX + MINX;
			p = Point(x, y);
		} while (pts.find(p) != pts.end());
		pts.insert(p);
	}

	int i = 0;
	For (set<Point>, p, pts) {
		if (i++ > 0) putchar(' ');
		printf("%.0lf %.0lf", p->x, p->y);
	}
	puts("");

	int q = crit ? MAXQ : rand() % MAXQ + 1;
	printf("%d\n", q);
	while (q--) {
		int x = rand() % RangeX + MINX;
		int y = rand() % RangeX + MINX;
		printf("%d %d\n", x, y);
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < NCRIT; ++i) test_case(true);
	while (T) test_case();

	return 0;
}

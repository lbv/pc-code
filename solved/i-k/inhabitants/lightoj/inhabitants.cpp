#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 100000


typedef unsigned int u32;
typedef long long GeomT;
typedef bool (*CmpT)(int, int);


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; b > 32; read()) v = v*10 + b-48; return s ? -v : v; }
};

#define eqz(x)   ((x) == 0)
#define cmp(a,b) ((a) - (b))

struct Point {
	GeomT x, y;
	Point() {}
	Point(GeomT X, GeomT Y) : x(X), y(Y) {}

//	void dbg() const { printf("P(%d, %d)", x, y); }

	bool is_collinear(const Point &a, const Point &b) const {
		return eqz(cross(a, b));
	}
	// cross product magnitude of {a}x{b}, relative to {this}
	GeomT cross(const Point &a, const Point &b) const {
		return (a.x-x)*(b.y-y) - (a.y-y)*(b.x-x);
	}

	bool in_box(const Point &a, const Point &b) const {
		GeomT lox = min(a.x, b.x), hix = max(a.x, b.x);
		GeomT loy = min(a.y, b.y), hiy = max(a.y, b.y);
		return cmp(lox, x) <= 0 && cmp(x, hix) <= 0 &&
			cmp(loy, y) <= 0 && cmp(y, hiy) <= 0;
	}

	bool is_between(const Point &a, const Point &b) const {
		return is_collinear(a, b) && in_box(a, b);
	}
};


Point pts[MAXN + 2];
int n;

// indices of points from which an edge goes right, up, left or down
int rt[MAXN], up[MAXN], lt[MAXN], dn[MAXN];
int nrt, nup, nlt, ndn;


bool cmp_rt(int i, int j) { return pts[i].x < pts[j].x; }
bool cmp_up(int i, int j) { return pts[i].y < pts[j].y; }
bool cmp_lt(int i, int j) { return pts[i].x > pts[j].x; }
bool cmp_dn(int i, int j) { return pts[i].y > pts[j].y; }

void process()
{
	pts[n] = pts[0];

	nrt = nup = nlt = ndn = 0;

	for (int i = 0; i < n; ++i) {
		Point &a = pts[i];
		Point &b = pts[i+1];

		if (a.x < b.x) rt[nrt++] = i;
		else if (a.x > b.x) lt[nlt++] = i;

		if (a.y < b.y) up[nup++] = i;
		else if (a.y > b.y) dn[ndn++] = i;
	}

	sort(rt, rt + nrt, cmp_rt);
	sort(up, up + nup, cmp_up);
	sort(lt, lt + nlt, cmp_lt);
	sort(dn, dn + ndn, cmp_dn);
}

bool check(int *mv, int nmv, CmpT cmpf, bool &res)
{
	int *pp;

	pp = upper_bound(mv, mv + nmv, n + 1, cmpf);
	if (pp-- == mv) {
		res = false;
		return true;
	}

	if (cmpf(*pp + 1, n+1)) {
		res = false;
		return true;
	}

	if (pts[n+1].is_between(pts[*pp], pts[*pp + 1])) {
		res = true;
		return true;
	}

	if (pts[n+1].cross(pts[*pp], pts[*pp + 1]) < 0) {
		res = false;
		return true;
	}

	return false;
}

bool solve(const Point &p)
{
	pts[n + 1] = p;

	bool result;
	if (check(rt, nrt, cmp_rt, result)) return result;
	if (check(up, nup, cmp_up, result)) return result;
	if (check(lt, nlt, cmp_lt, result)) return result;
	if (check(dn, ndn, cmp_dn, result)) return result;

	return true;
}

int main()
{
	Reader rr;

	int T = rr.next_u32();

	int ncase = 0;
	while (T--) {
		n = rr.next_u32();
		for (int i = 0; i < n; ++i) {
			int x = rr.next_int();
			int y = rr.next_int();
			pts[i] = Point(x, y);
		}
		process();

		printf("Case %d:\n", ++ncase);

		Point p;
		int Q = rr.next_u32();

		while (Q--) {
			int x = rr.next_int();
			int y = rr.next_int();

			if (solve(Point(x, y))) puts("y");
			else puts("n");
		}
	}

	return 0;
}

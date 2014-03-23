#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;


#define EPS (1e-9)
#define Abs(x) (fabs(x))


const double pi = acos(-1.0);
const double pi_t2 = acos(-1.0) * 2;


bool eqz(double x) { return fabs(x) < EPS; }
double sanitize(double x) { return eqz(x) ? 0.0 : x; }
int cmp(double a, double b) {
	double s;
	if (eqz(s = a-b)) return 0;
	return s < 0 ? -1 : 1;
}

template <typename T>
struct _Point {
	T x, y;
	_Point(): x(0), y(0) {}
	_Point(T X, T Y) : x(X), y(Y) {}

	T distance(const _Point &p) const {
		T dx = p.x - x, dy = p.y - y; return sqrt(dx*dx + dy*dy);
	}
	bool operator==(const _Point &p) const {
		return cmp(x, p.x) == 0 && cmp(y, p.y) == 0;
	}
	bool operator!=(const _Point &p) const { return !(*this == p); }
	void print() const {
		printf("(%2.1lf, %2.1lf)\n", x, y);
	}
};
typedef _Point<double> Point;


double circle_angle(double a) { return (a=sanitize(a)) >= 0.0 ? a : a+pi_t2; }


double heron(double a, double b, double c)
{
	double s = (a + b + c) / 2.0;
	return sqrt(s * (s - a) * (s - b) * (s - c));
}

// angle between a (as a vector) and b (as a vector)
double arc_angle(const Point &a, const Point &b)
{
	return circle_angle(atan2(b.y, b.x) - atan2(a.y, a.x));
}

// cross product magnitude of axb, relative to (0,0)
double cross(const Point &a, const Point &b)
{
	return a.x*b.y - a.y*b.x;
}
// returns the sign of the cross product
double cross_sgn(const Point &a, const Point &b)
{
	double c = sanitize(cross(a, b));
	return c == 0.0 ? c : c / Abs(c);
}

// area between (0,0), a, b
double tri_area(const Point &a, const Point &b)
{
	double s1 = sqrt(a.x*a.x + a.y*a.y);
	double s2 = sqrt(b.x*b.x + b.y*b.y);
	double s3 = a.distance(b);

	return heron(s1, s2, s3);
}


int r, lt, rt, bt, tp;

Point crit[16];
int ncrit;



bool is_triangular_sector(const Point &a, const Point &b)
{
	if (cmp(a.y, tp) == 0 && cmp(b.y, tp) == 0 && tp >= 0)
		return true;
	if (cmp(a.y, bt) == 0 && cmp(b.y, bt) == 0 && bt <= 0)
		return true;
	if (cmp(a.x, rt) == 0 && cmp(b.x, rt) == 0 && rt >= 0)
		return true;
	if (cmp(a.x, lt) == 0 && cmp(b.x, lt) == 0 && lt <= 0)
		return true;
	return false;
}

void uniq_crit()
{
	if (ncrit < 2) return;

	int tmp = ncrit;
	ncrit = 1;
	for (int i = 1; i < tmp; ++i)
		if (crit[i] != crit[ncrit-1]) crit[ncrit++] = crit[i];
}

#define Add(x,y) (crit[ncrit++] = Point((x), (y)))
double solve()
{
	// base cases: the circle is completely outside...
	if (rt <= -r || tp <= -r || lt >= r || bt >= r)
		return 0.0;
	// ... or completely inside the rectangle
	if (lt <= -r && bt <= -r && rt >= r && tp >= r)
		return pi * r * r;

	// compact the rectangle so it touches the circle, if possible
	if (tp > r)  tp = max(bt, r);
	if (lt < -r) lt = min(rt, -r);
	if (bt < -r) bt = min(tp, -r);
	if (rt > r)  rt = max(lt, r);

	// squares of basic values
	int r2, lt2, rt2, bt2, tp2;

	r2 = r*r;
	lt2 = lt*lt;
	rt2 = rt*rt;
	bt2 = bt*bt;
	tp2 = tp*tp;

	// find critical points
	double x, y;

	ncrit = 0;
	if (lt2 + bt2 <= r2) Add(lt, bt);

	if (-r <= bt && bt <= r) {
		x = sqrt(r2 - bt2);
		if (lt <= -x && -x <= rt) Add(-x, bt);
		if (lt <=  x &&  x <= rt) Add(x, bt);
	}

	if (rt2 + bt2 <= r2) Add(rt, bt);

	if (-r <= rt && rt <= r) {
		y = sqrt(r2 - rt2);
		if (bt <= -y && -y <= tp) Add(rt, -y);
		if (bt <=  y &&  y <= tp) Add(rt, y);
	}

	if (rt2 + tp2 <= r2) Add(rt, tp);

	if (-r <= tp && tp <= r) {
		x = sqrt(r2 - tp2);
		if (lt <=  x &&  x <= rt) Add(x, tp);
		if (lt <= -x && -x <= rt) Add(-x, tp);
	}

	if (lt2 + tp2 <= r2) Add(lt, tp);

	if (-r <= lt && lt <= r) {
		y = sqrt(r2 - lt2);
		if (bt <=  y &&  y <= tp) Add(lt, y);
		if (bt <= -y && -y <= tp) Add(lt, -y);
	}

	// remove duplicates
	uniq_crit();

	if (ncrit < 2) return 0.0;

	/*
	printf("  %d crits:\n", ncrit);
	for (int i = 0; i < ncrit; ++i) {
		printf("  :: "); crit[i].print();
	}
	*/

	double ans = 0.0;

	for (int i = 0; i < ncrit; ++i) {
		Point &a = crit[i];
		Point &b = crit[(i+1) % ncrit];

		double sgn = cross_sgn(a, b);
		if (sgn < 0.0) {
			ans -= tri_area(a, b);
			continue;
		}
		if (is_triangular_sector(a, b))
			ans += tri_area(a, b);
		else
			ans += arc_angle(a, b) * r2 / 2.0;

		//printf("    area so far: %.2lf\n", ans);
	}

	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	int x, y;
	int ncase = 0;
	while (T--) {
		scanf("%d%d%d%d%d%d%d", &x, &y, &r, &lt, &bt, &rt, &tp);

		// translate coordinates so the center of the circle is (0,0)
		lt -= x;
		rt -= x;
		bt -= y;
		tp -= y;

		printf("Case %d: %.8lf\n", ++ncase, solve());
	}

	return 0;
}

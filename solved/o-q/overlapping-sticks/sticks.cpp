#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 100000
#define MINX -1000000
#define INF  2000010


typedef unsigned int u32;
typedef long long i64;


struct Reader {
	int b; Reader() { read(); }
	void read() { b = getchar_unlocked(); }
	void skip() { while (0 <= b && b <= 32) read(); }

	u32 next_u32() {
		u32 v=0; for (skip(); 48<=b&&b<=57; read()) v = 10*v+b-48; return v; }
	int next_int() {
		int v = 0; bool s = false;
		skip(); if (b == '-') { s = true; read(); }
		for (; 48<=b&&b<=57; read()) v = v*10 + b-48; return s ? -v : v; }
};

template<typename T>
T gcd(T a, T b) { for (T c = a%b; c != 0; a=b,b=c,c=a%b); return b; }


struct SegPoint {
	i64 p, q;  // slope = p/q
	i64 b;     // y-intercept
	int x;
	int t;     // 0: first point of a segment, 1: second point

	SegPoint() {}
	SegPoint(i64 P, i64 Q, i64 B, int X, int T):
		p(P), q(Q), b(B), x(X), t(T) {}

	bool operator<(const SegPoint &z) const {
		if (p != z.p || q != z.q) return p*z.q < z.p*q;
		if (b != z.b) return b < z.b;
		if (x != z.x) return x < z.x;
		return t > z.t;
	}
};



int N;
SegPoint pts[MAXN*2];


i64 solve()
{
	sort(pts, pts + 2*N);

	int cnt = 0;
	i64 ans = 0;

	for (int i = 0, I = 2*N; i < I; ++i)
		if (pts[i].t == 1) --cnt;
		else ans += cnt++;

	return ans;
}

void simplify(i64 &p, i64 &q)
{
	i64 g = gcd(p, q);
	p /= g;
	q /= g;
}

int main()
{
	Reader rr;
	int T = rr.next_u32();

	int ncase = 0;
	while (T--) {
		N = rr.next_u32();
		for (int i = 0; i < N; ++i) {
			int x1 = rr.next_int() - MINX;
			int y1 = rr.next_int() - MINX;
			int x2 = rr.next_int() - MINX;
			int y2 = rr.next_int() - MINX;

			i64 p, q, b;
			int u, v;
			if (x1 == x2)
				p = INF, q = 1;
			else
				p = y2-y1, q = x2-x1;

			simplify(p, q);

			if (x1 == x2)
				b = x1, u = y1, v = y2;
			else
				b = q*y1 - p*x1, u = x1, v = x2;

			if (u > v) swap(u, v);
			pts[i*2]   = SegPoint(p, q, b, u, 0);
			pts[i*2+1] = SegPoint(p, q, b, v, 1);
		}

		printf("Case %d: %lld\n", ++ncase, solve());
	}

	return 0;
}

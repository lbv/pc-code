#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 30000
#define MAXS (MAXN*2)
#define MAXH (MAXN*4)

#define Memset(m,v) memset(m, v, sizeof(m))
#define Clr(m) Memset(m,0)


typedef long long i64;
typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};


struct Segment {
	int x;
	int s;     // s=1 if it's the leftmost segment of a rectangle, -1 otherwise
	int y[2];  // y[0]: lowest y-coordinate, y[1]: highest
	int i[2];  // indices of the y coordinates in the sorted array

	Segment() {}
	Segment(int X, int Y1, int Y2, int S): x(X), s(S) { y[0] = Y1, y[1] = Y2; }
	bool operator<(const Segment &o) const {
		if (x != o.x) return x < o.x;
		return s > o.s;
	}
};

struct Height {
	int y;
	int s;  // index of the segment that has this height
	int c;  // which y-coordinate is this (0 or 1)

	Height() {}
	Height(int Y, int S, int C): y(Y), s(S), c(C) {}

	bool operator<(const Height &h) const { return y < h.y; }
};


// Unique y-coordinates
int ys[MAXH];
int yn;


//
// Segment Tree
//
#define LOGH 18  // 1 + ceil(log2(MAXH))
struct SegTree {
	struct Node {
		int a;	// 1-D covered area
		int n;	// number of segments that fully intersect with this node
	};

	Node T[1 << LOGH];
	int n;

	void init(int N) { n = N; Clr(T); }

	void set_area(int v, int x, int a, int b, bool is_leaf) {
		if (T[x].n > 0)
			T[x].a = ys[b] - ys[a];
		else if (is_leaf)
			T[x].a = 0;
		else {
			int lt = 2*x, rt = lt + 1;
			T[x].a = T[lt].a + T[rt].a;
		}
	}

	void update(int i, int j, int v) { tree_update(i, j, v, 1, 0, n-1); }
	void tree_update(int i, int j, int v, int x, int a, int b) {
		if (j <= a || i >= b) return;
		if (a == b - 1) {
			T[x].n += v;
			set_area(v, x, a, b, true);
			return;
		}

		int lt = 2*x, rt = lt + 1, md = (a+b)/2;
		if (a >= i && b <= j) {
			T[x].n += v;
			set_area(v, x, a, b, false);
			return;
		}
		tree_update(i, j, v, lt, a, md);
		tree_update(i, j, v, rt, md, b);
		set_area(v, x, a, b, false);
	}
};


int n, x1, y1, x2, y2;

Segment ss[MAXS];
Height hs[MAXH];
int sn, hn;

SegTree tree;


i64 solve()
{
	sort(ss, ss + sn);

	// Setup ys, to reduce the range from [0:10^9] to [0:MAXH]
	hn = 0;
	for (int i = 0; i < sn; ++i) {
		Segment &s = ss[i];

		hs[hn++] = Height(s.y[0], i, 0);
		hs[hn++] = Height(s.y[1], i, 1);
	}

	sort(hs, hs + hn);

	yn = 0;
	for (int i = 0; i < hn; ++i) {
		Height &h = hs[i];

		if (i == 0 || h.y != hs[i-1].y)
			ys[yn++] = h.y;

		ss[h.s].i[h.c] = yn - 1;
	}

	tree.init(yn);
	i64 ans = 0;

	for (int i = 0; i < sn; ++i) {
		Segment &s = ss[i];

		if (i > 0 && s.x != ss[i-1].x)
			ans += 1LL * tree.T[1].a * (s.x - ss[i-1].x);

		tree.update(s.i[0], s.i[1], s.s);
	}

	return ans;
}

int main()
{
	Reader rr;
	int T = rr.next_u32();

	int ncase = 0;
	while (T--) {
		n = rr.next_u32();

		sn = 0;
		for (int i = 0; i < n; ++i) {
			x1 = rr.next_u32();
			y1 = rr.next_u32();
			x2 = rr.next_u32();
			y2 = rr.next_u32();

			ss[sn++] = Segment(x1, y1, y2, 1);
			ss[sn++] = Segment(x2, y1, y2, -1);
		}

		printf("Case %d: %lld\n", ++ncase, solve());
	}

	return 0;
}

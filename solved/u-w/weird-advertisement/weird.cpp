#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 30000
#define MAXK 10

#define Clr(m) memset(m, 0, sizeof(m))


typedef unsigned int u32;
typedef long long i64;


struct Reader {
	int b; Reader() { read(); }
	void read() { b = getchar_unlocked(); }
	void skip() { while (0 <= b && b <= 32) read(); }

	u32 next_u32() {
		u32 v=0; for (skip(); 48<=b&&b<=57; read()) v = 10*v+b-48; return v; }
};


int uhs[MAXN*2];   // unique heights
int nuhs, k;


//
// Segment Tree
//
#define TreeIsLeaf (a == b)
#define TreeIsOut  (j < a || b < i)
#define TreeIsIn   (i <= a && b <= j)
#define TreeLeft   2*x, a, (a+b)/2
#define TreeRight  2*x+1, (a+b)/2+1, b

#define Tree  (T[x])
#define Left  (T[2*x])
#define Right (T[2*x+1])

#define Range (uhs[b+1] - uhs[a])

#define LOGN 17  // 1 + ceil(log2(MAXN))
struct SegTree {
	struct Node {
		int c;          // # of rectangles that completely cover this range
		int r[MAXK+1];  // r[i]: # of points covered by i rectangles
	};

	Node T[1 << LOGN];
	int n;

	void init(int N) { n = N; init(1, 0, n-1); }
	void init(int x, int a, int b) {
		Tree.c = 0;
		Clr(Tree.r);
		if (TreeIsLeaf) {
			Tree.r[0] = Range;
			return;
		}
		init(TreeLeft);
		init(TreeRight);
		Tree.r[0] = Left.r[0] + Right.r[0];
	}

	void update(int i, int j, int v) { update(i, j, v, 1, 0, n-1); }
	void update(int i, int j, int v, int x, int a, int b) {
		if (TreeIsOut) return;

		if (TreeIsIn)
			Tree.c += v;
		else {
			update(i, j, v, TreeLeft);
			update(i, j, v, TreeRight);
		}

		Clr(Tree.r);
		if (TreeIsLeaf) Tree.r[min(k, Tree.c)] = Range;
		else
			for (int i = 0; i <= k; ++i) {
				int idx = min(k, Tree.c + i);
				Tree.r[idx] += Left.r[i] + Right.r[i];
			}
	}

	int query() { return T[1].r[k]; }
};
SegTree stree;


struct Seg {
	int x, y1, y2, v;

	bool operator<(const Seg &s) const { return x < s.x; }
};
Seg segs[MAXN*2];
int nsegs;

struct Height {
	int y, i, t;

	bool operator<(const Height &h) const { return y < h.y; }
};
Height hs[MAXN*2];


int n;


i64 solve()
{
	sort(uhs, uhs + nsegs);
	nuhs = unique(uhs, uhs + nsegs) - uhs;

	sort(hs, hs + nsegs);
	for (int i = 0, j = 0; i < nsegs; ++i) {
		if (uhs[j] != hs[i].y) ++j;

		int idx = hs[i].i;
		if (hs[i].t == 0)
			segs[idx].y1 = segs[idx + 1].y1 = j;
		else
			segs[idx].y2 = segs[idx + 1].y2 = j;
	}

	sort(segs, segs + nsegs);
	stree.init(nuhs - 1);

	i64 ans = 0;
	int cells = 0, prevx = 0;

	for (int i = 0; i < nsegs; ++i) {
		int x = segs[i].x;

		if (x != prevx) {
			ans += 1LL * cells * (x - prevx);
			prevx = x;
		}

		stree.update(segs[i].y1, segs[i].y2-1, segs[i].v);
		cells = stree.query();
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
		k = rr.next_u32();

		nsegs = 0;
		for (int i = 0; i < n; ++i) {
			int x1 = rr.next_u32();
			int y1 = rr.next_u32();
			int x2 = rr.next_u32();
			int y2 = rr.next_u32();

			hs[nsegs] = (Height) { y1, nsegs, 0 };
			hs[nsegs + 1] = (Height) { y2 + 1, nsegs, 1 };

			uhs[nsegs] = y1;
			uhs[nsegs + 1] = y2 + 1;

			segs[nsegs++] = (Seg) { x1, y1, y2, 1 };
			segs[nsegs++] = (Seg) { x2 + 1, y1, y2, -1 };
		}

		printf("Case %d: %lld\n", ++ncase, solve());
	}

	return 0;
}

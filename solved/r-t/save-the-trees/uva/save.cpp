#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN    100000
#define MAXTYPE 100000

#define INF 0x3f3f3f3f3f3f3f3fLL

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


typedef unsigned int u32;
typedef long long i64;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (0 <= b && b <= 32) read(); }

    u32 next_u32() {
        u32 v=0; for (skip(); 48<=b&&b<=57; read()) v = 10*v+b-48; return v; }
};


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

#define LOGN 18  // 1 + ceil(log2(MAXN))
struct SegTree {
	struct Node {
		i64 d;  // D.P. calculation up to the given node
		int t;  // height of the tallest tree after the node
		i64 s;  // sum d+t
		int p;  // propagation for t

		void set_d(i64 D) { d=D; s = d+t; }
		void set_t(int T) { t=T; s = d+t; }
		void set_from(const Node &x) {
			d = x.d;
			t = x.t;
			s = x.s;
		}
	};

	Node T[1 << LOGN];
	int n;

	void init(int N) { n = N; init(1, 0, n-1); }
	void init(int x, int a, int b) {
		Tree.d = Tree.s = INF;
		Tree.t = Tree.p = 0;
		if (TreeIsLeaf) return;
		init(TreeLeft);
		init(TreeRight);
	}

	void propagate(int x, int a, int b) {
		if (Tree.p == 0) return;
		Tree.set_t(Tree.p);
		if (! TreeIsLeaf)
			Left.p = Right.p = Tree.p;
		Tree.p = 0;
	}

	void update_t(int i, int j, int v) { update_t(i, j, v, 1, 0, n-1); }
	void update_t(int i, int j, int v, int x, int a, int b) {
		propagate(x, a, b);
		if (TreeIsOut) return;
		if (TreeIsLeaf) { Tree.set_t(v); return; }

		if (TreeIsIn) {
			Tree.set_t(v);
			Tree.set_d(Left.d);
			Left.p = Right.p = v;
			return;
		}
		update_t(i, j, v, TreeLeft);
		update_t(i, j, v, TreeRight);
		Tree.s = min(Left.s, Right.s);
	}

	void update_d(int i, int j, i64 v) { update_d(i, j, v, 1, 0, n-1); }
	void update_d(int i, int j, i64 v, int x, int a, int b) {
		propagate(x, a, b);
		if (TreeIsOut) return;
		if (TreeIsLeaf) { Tree.set_d(v); return; }

		update_d(i, j, v, TreeLeft);
		update_d(i, j, v, TreeRight);
		Tree.s = min(Left.s, Right.s);
		Tree.d = Left.d;
	}

	i64 query(int i, int j) { return query(i, j, 1, 0, n-1); }
	i64 query(int i, int j, int x, int a, int b) {
		if (TreeIsOut) return INF;
		propagate(x, a, b);
		if (TreeIsIn) return Tree.s;
		i64 q1 = query(i, j, TreeLeft);
		i64 q2 = query(i, j, TreeRight);
		return min(q1, q2);
	}

};

#define LOGH 16  // 1 + ceil(log2(max height))
struct SegTreeH {
	struct Node {
		int i;  // index of most recent tree with this height
		int p;  // propagation
	};

	Node T[1 << LOGH];
	int n;

	void init(int N) { n = N; Neg(T); }

	void propagate(int x, int a, int b) {
		if (Tree.p < 0) return;
		Tree.i = Tree.p;
		if (! TreeIsLeaf)
			Left.p = Right.p = Tree.p;
		Tree.p = -1;
	}

	void update(int i, int j, int v) { update(i, j, v, 1, 0, n-1); }
	void update(int i, int j, int v, int x, int a, int b) {
		propagate(x, a, b);
		if (TreeIsOut) return;
		if (TreeIsLeaf) { Tree.i = v; return; }

		if (TreeIsIn) {
			Tree.i = v;
			Left.p = Right.p = v;
			return;
		}
		update(i, j, v, TreeLeft);
		update(i, j, v, TreeRight);
		Tree.i = Right.i;
	}

	int query(int i, int j) { return query(i, j, 1, 0, n-1); }
	int query(int i, int j, int x, int a, int b) {
		if (TreeIsOut) return -1;
		propagate(x, a, b);
		if (TreeIsIn) return Tree.i;
		int q1 = query(i, j, TreeLeft);
		int q2 = query(i, j, TreeRight);
		return max(q1, q2);
	}

};


int N;
int ts[MAXN+1];  // types
int hs[MAXN+1];  // heights

int hi;  // height of tallest tree

// last[t]: index of the last tree of type t seen
int last[MAXTYPE+1];

// from[i]: index of the leftmost location where a group can start that
// includes the i-th tree
int from[MAXN+1];

SegTree stree;
SegTreeH streeh;



i64 solve()
{
	Neg(last);

	for (int i = 1; i <= N; ++i) {
		from[i] = from[i - 1];
		if (last[ts[i]] >= 0) from[i] = max(from[i], last[ts[i]]);
		last[ts[i]] = i;
	}

	streeh.init(hi + 1);
	streeh.update(1, hi, 0);

	stree.init(N+1);
	stree.update_d(0, 0, 0);

	i64 ans = 0;

	for (int i = 1; i <= N; ++i) {
		int idx = streeh.query(hs[i], hs[i]);
		streeh.update(1, hs[i], i);

		stree.update_t(idx, i - 1, hs[i]);
		ans = stree.query(from[i], i - 1);
		stree.update_d(i, i, ans);
	}

	return ans;
}

int main()
{
	Reader rr;
	int T = rr.next_u32();

	int ncase = 0;
	while (T--) {
		N = rr.next_u32();
		hi = 0;
		for (int i = 1; i <= N; ++i) {
			ts[i] = rr.next_u32();
			hs[i] = rr.next_u32();
			if (hs[i] > hi) hi = hs[i];
		}
		printf("Case %d: %lld\n", ++ncase, solve());
	}

	return 0;
}

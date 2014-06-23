#include <cstdio>


#define MAXN 100000


typedef unsigned int u32;


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
	char next_char() { skip(); char c = b; read(); return c; }
	bool has_next() { skip(); return b > 0; }
};


int A[MAXN];

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
		int s;  // product sign
	};

	Node T[1 << LOGN];
	int n;

	void init(int N) { n = N; init(1, 0, n-1); }
	void init(int x, int a, int b) {
		if (TreeIsLeaf) {
			Tree.s = A[a];
			return;
		}
		init(TreeLeft);
		init(TreeRight);
		Tree.s = Left.s * Right.s;
	}

	void update(int i, int j, int v) { update(i, j, v, 1, 0, n-1); }
	void update(int i, int j, int v, int x, int a, int b) {
		if (TreeIsOut) return;
		if (TreeIsLeaf) { Tree.s = v; return; }

		update(i, j, v, TreeLeft);
		update(i, j, v, TreeRight);
		Tree.s = Left.s * Right.s;
	}

	int query(int i, int j) { return query(i, j, 1, 0, n-1); }
	int query(int i, int j, int x, int a, int b) {
		if (TreeIsOut) return 1;
		if (TreeIsIn) return Tree.s;
		int q1 = query(i, j, TreeLeft);
		int q2 = query(i, j, TreeRight);
		return q1 * q2;
	}

};


int N, K;
SegTree segtree;


int sgn(int x)
{
	if (x < 0) return -1;
	if (x > 0) return 1;
	return 0;
}

int main()
{
	Reader rr;
	while (rr.has_next()) {
		N = rr.next_u32();
		K = rr.next_u32();

		for (int i = 0; i < N; ++i)
			A[i] = sgn(rr.next_int());

		segtree.init(N);

		while (K--) {
			char cmd = rr.next_char();
			if (cmd == 'C') {
				int i = rr.next_u32() - 1;
				int x = sgn(rr.next_int());

				segtree.update(i, i, x);
			}
			else if (cmd == 'P') {
				int i = rr.next_u32() - 1;
				int j = rr.next_u32() - 1;
				int x = segtree.query(i, j);

				if (x == 0) putchar('0');
				else putchar(x < 0 ? '-' : '+');
			}
		}
		putchar('\n');
	}

	return 0;
}

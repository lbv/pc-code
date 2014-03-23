#include <cmath>
#include <cstdio>
#include <cstring>


#define MAXN 100000
#define LOGN 18

#define Memset(m,v) memset(m, v, sizeof(m))
#define Neg(m) Memset(m,-1)


typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};

int val[MAXN];

struct LCA {
	int L[MAXN];		// L[i]: level of node i
	int A[MAXN][LOGN];	// A[i][j]: 2^j'th ancestor of i
	int n, h, lh;		// n, height, log(h)
	LCA() {}

	void init(int N, int H) { n=N, h=H; Neg(A); lh = log2(h); }
	void process() {
		// precond: A[i][0] is set for all i
		for (int j = 1, p = 2; p < h; ++j, p <<= 1)
			for (int i = 0; i < n; ++i)
				if (A[i][j-1] != -1)
					A[i][j] = A[ A[i][j-1] ][j-1];
	}
	int query(int k, int v) {
		for (int i = lh, p = 1 << lh; i >= 0; --i, p >>= 1)
			if (L[k] - p >= 0 && val[A[k][i]] >= v) k = A[k][i];
		return k;
	}
};


int N, q;
LCA tree;


void find_level(int v)
{
	int p = tree.A[v][0];
	if (tree.L[p] < 0) find_level(p);
	tree.L[v] = tree.L[p] + 1;
}

void process()
{
	// calculate levels of all nodes
	Neg(tree.L);
	tree.L[0] = 0;
	for (int i = 1; i < N; ++i)
		if (tree.L[i] < 0) find_level(i);

	tree.process();
}

int main()
{
	Reader rr;
	int T = rr.next_u32();

	int ncase = 0;
	while (T--) {
		N = rr.next_u32();
		q = rr.next_u32();

		tree.init(N, N);
		val[0] = 1;

		for (int i = 1; i < N; ++i) {
			tree.A[i][0] = rr.next_u32();
			val[i] = rr.next_u32();
		}

		process();

		printf("Case %d:\n", ++ncase);
		while (q--) {
			int k = rr.next_u32();
			int v = rr.next_u32();

			printf("%d\n", tree.query(k, v));
		}
	}

	return 0;
}

//
// Trie
//
struct Trie {
	struct Node {
		int ch[8];
		int n;
	};
	Node nodes[MAX_NODES];
	int n;

	void init() { Clr(nodes); n = 1; }
	int insert(const char *s) {
		int i = 0;
		for (; *s; ++s) {
			int idx = *s - 'A';
			if (nodes[i].ch[idx] == 0)
				nodes[i].ch[idx] = n++;
			i = nodes[i].ch[idx];
		}
		return ++nodes[i].n;
	}
};

//
// Hash Map
//
struct HashT {
	int k, v;

	bool operator==(const HashT &x) const { return k == x.k; }
};
const int HASHB = 1 << 15;
const int HASHN = 1000000;
#define HASHT_SZ(x)  (sizeof(int))
#define HASHT_PTR(x) (reinterpret_cast<const u8*>(&( (x).k )))
struct HashMap {
	HashT data[HASHN];
	int next[HASHN];
	int buckets[HASHB];
	int n;

	void init() { Neg(buckets); n = 0; }
	u32 fnv_hash(const u8 *p, int n) const {
		u32 h = 2166136261U;
		for (int i = 0; i < n; ++i) h = (h * 16777619U) ^ p[i];
		return h;
	}

	// Adds an element to the hash map. Returns null if it is a new element,
	// or a pointer to a HashT if it was already stored.
	HashT *add(HashT &h) {
		int b = fnv_hash(HASHT_PTR(h), HASHT_SZ(h)) % HASHB;
		for (int i = buckets[b]; i >= 0; i = next[i])
			if (data[i] == h) return &data[i];
		next[n] = buckets[b], buckets[b] = n, data[n++] = h;
		return NULL;
	}

	// Finds an element in the hash map. Returns a pointer if found, or NULL
	// otherwise.
	HashT *find(HashT &h) {
		int b = fnv_hash(HASHT_PTR(h), HASHT_SZ(h)) % HASHB;
		for (int i = buckets[b]; i >= 0; i = next[i])
			if (data[i] == h) return &data[i];
		return NULL;
	}
};


//
// Binary Indexed Tree
//
const int MAXBIT = MAXN;
typedef int BitT;
struct Bit {
	BitT f[MAXBIT + 1];
	int n;
	void init(int N) { n=N; memset(f, 0, sizeof(BitT) * (n+1)); }
	void add(int i, BitT v) { while (i <= n) { f[i] += v; i += GetLSB(i); } }
	BitT query(int i) { BitT r = 0; for (;i; ClrLSB(i)) r += f[i]; return r; }
	BitT query(int from, int to) { return query(to) - query(from - 1); }
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

#define LOGN 19  // 1 + ceil(log2(MAXN))
struct SegTree {
	struct Node {
		int i;  // some value
		int p;  // propagation
	};

	Node T[1 << LOGN];
	int n;

	void init(int N) { n = N; init(1, 0, n-1); }
	void init(int x, int a, int b) {
		Tree.i = Tree.p = -1;
		if (TreeIsLeaf) return;
		init(TreeLeft);
		init(TreeRight);
	}

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


//
// R-Tree for 2D matrices
//
const int MAX_ROWS = MAXN;
const int MAX_COLS = MAXN;
const int MAX_H    = 19;   // 1 + ceil(log2(MAX_ROWS * MAX_COLS))
template <typename NT>
struct R2Tree {
	struct Node { NT v; };

	Node T[1 << MAX_H];
	NT	 M[MAX_ROWS][MAX_COLS];
	int  r, c;

	void init(int R, int C) { tree_init(1, 0, 0, r=R, c=C, 0); }
	void tree_init(int x, int r1, int c1, int r2, int c2, int o) {
		if (r1 == r2 && c1 == c2) {
			T[x].v = M[r1][c1];
			return;
		}

		int op = (o + 1) % 2;
		int lt = 2*x, rt = lt + 1;
		if ((o == 0 && c1 < c2) || r1 == r2) {
			int md = (c1 + c2) / 2;
			tree_init(lt, r1, c1, r2, md, op);
			tree_init(rt, r1, md + 1, r2, c2, op);
		}
		else {
			int md = (r1 + r2) / 2;
			tree_init(lt, r1, c1, md, c2, op);
			tree_init(rt, md + 1, c1, r2, c2, op);
		}
		T[x].v = max(T[lt].v, T[rt].v);
	}

	int qr1, qc1, qr2, qc2;
	NT get(int r1, int c1, int r2, int c2) {
		qr1 = r1, qc1 = c1, qr2 = r2, qc2 = c2;
		return tree_get(1, 0, 0, r, c, 0);
	}
	NT tree_get(int x, int r1, int c1, int r2, int c2, int o) {
		if (r1 >= qr1 && r2 <= qr2 && c1 >= qc1 && c2 <= qc2) return T[x].v;
		if (r1 > qr2 || r2 < qr1 || c1 > qc2 || c2 < qc1) return -1;

		int op = (o + 1) % 2;
		int lt = 2*x, rt = lt + 1;
		NT a, b;
		if ((o == 0 && c1 < c2) || r1 == r2) {
			int md = (c1 + c2) / 2;
			a = tree_get(lt, r1, c1, r2, md, op);
			b = tree_get(rt, r1, md + 1, r2, c2, op);
		}
		else {
			int md = (r1 + r2) / 2;
			a = tree_get(lt, r1, c1, md, c2, op);
			b = tree_get(rt, md + 1, c1, r2, c2, op);
		}
		return max(a, b);
	}
};

//
// Lowest Common Ancestor
//
struct LCA {
	int L[MAXN];        // L[i]: level of node i
	int A[MAXN][LOGN];  // A[i][j]: 2^j'th ancestor of i
	int n, h, lh;       // n, height, log(h)
	LCA() {}

	void init(int N, int H) { n=N, h=H; Neg(A); lh = log2(h); }
	void process() {
		// precond: A[i][0] is set for all i
		for (int j = 1, p = 2; p < h; ++j, p <<= 1)
			for (int i = 0; i < n; ++i)
				if (A[i][j-1] != -1)
					A[i][j] = A[ A[i][j-1] ][j-1];
	}
	int query_orig(int a, int b) {
		if (L[a] < L[b]) swap(a, b);

		for (int i = lh, p = 1 << lh; i >= 0; --i, p >>= 1)
			if (L[a] - p >= L[b]) a = A[a][i];
		if (a == b) return a;

		for (int i = lh; i >= 0; --i)
			if (A[a][i] != -1 && A[a][i] != A[b][i])
				a = A[a][i], b = A[b][i];
		return A[a][0];
	}
};

//
// Sparse Table
//
struct SparseTable {
	SparseT A[MAX_SPARSE];
	SparseT M[MAX_SPARSE][LOG_SPARSE];	// 1 + ceil(log2(MAX_SP))
	SparseTable() {}
	void init(int n) {
		for (int i = 0; i < n; ++i) M[i][0] = i;
		for (int j = 1, p = 2, q = 1; p <= n; ++j, p <<= 1, q <<= 1)
			for (int i = 0; i + p - 1 < n; ++i) {
				int a = M[i][j - 1], b = M[i + q][j - 1];
				M[i][j] = A[a] <= A[b] ? a : b;
			}
	}
	SparseT query_val(int i, int j) { return A[query_idx(i, j)]; }
	int query_idx(int i, int j) {
		int k = log2(j - i + 1);
		int a = M[i][k], b = M[j + 1 - (1<<k)][k];
		return A[a] <= A[b] ? a : b;
	}
};

//
// Binary Search Tree
//
const int Nil = 0;
#define LT(t)  (T[T[t].l])
#define RT(t)  (T[T[t].r])
#define PAR(t) (T[T[t].p])
struct Bst {
	struct Node {
		int p, l, r, s, k;	// parent, left, right, size, key
		void init(int K) { k = K; p = l = r = Nil; s = 1; }
		void clear() { p = l = r = s = k = 0; }
	};
	int K[MAXK];
	Node T[MAXK + 1];
	int root, sz;
	int get(int t) { return K[T[t].k]; }
	int size() { return T[root].s; }
	void init(int n) { T[0].clear(); sz = 0; root = init_tree(0, n - 1); }
	int init_tree(int a, int b) {
		if (a > b) return Nil;
		int t = ++sz;
		if (a == b) { T[t].init(a); return t; }
		int m = (a + b) / 2;
		T[t].l = init_tree(a, m - 1);
		T[t].r = init_tree(m + 1, b);
		T[t].p = Nil, T[t].k = m, T[t].s = 1 + LT(t).s + RT(t).s;
		LT(t).p = t; RT(t).p = t;
		return t;
	}
	int find_kth(int k) { return find_kth_tree(k, root); }
	int find_kth_tree(int k, int t) {
		if (LT(t).s > k) return find_kth_tree(k, T[t].l);
		k -= LT(t).s;
		if (k == 0) return t;
		if (--k >= RT(t).s) return Nil;
		return find_kth_tree(k, T[t].r);
	}
	void remove(int t) {
		int x;
		if (T[t].l != Nil && T[t].r != Nil) {
			if (RT(t).s >= LT(t).s) for (x=T[t].r; T[x].l != Nil; x=T[x].l) ;
			else					for (x=T[t].l; T[x].r != Nil; x=T[x].r) ;
			T[t].k = T[x].k;
			t = x;
		}
		if (T[t].l == Nil && T[t].r == Nil) {
			if (T[t].p == Nil) { root = Nil; return; }
			if (PAR(t).l == t) PAR(t).l = Nil;
			else			   PAR(t).r = Nil;
		}
		else {
			x = T[t].l != Nil ? T[t].l : T[t].r;
			if (T[t].p == Nil) { T[root = x].p = Nil; return; }
			if (PAR(t).l == t) PAR(t).l = x;
			else			   PAR(t).r = x;
			T[x].p = T[t].p;
		}
		for (x = T[t].p; x != Nil; x = T[x].p) --T[x].s;
	}
};

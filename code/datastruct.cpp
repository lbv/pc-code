//
// Trie
//
struct Trie {
    struct Node {
        int ch[26];
        int n;
        Node() { n=0; Zero(ch); }
    };
    int sz;
    vector<Node> nodes;
    void init() { nodes.clear(); nodes.resize(1); sz = 1; }
    void insert(const char *s) {
        int idx, cur = 0;

        for (; *s; ++s) {
            idx = *s - 'A';
            if (! nodes[cur].ch[idx]) {
                nodes[cur].ch[idx] = sz++;
                nodes.resize(sz);
            }

            cur = nodes[cur].ch[idx];
        }
    }
};

//
// Hash Map
//
#define HASHB 4096
const size_t KeySz = sizeof(int) * 5;
struct HM {
    struct Key {
        int n[5];
        Key(int *N) { memcpy(n, N, KeySz); sort(n, n + 5); }
        bool operator==(const Key &x) const {
            return memcmp(n, x.n, KeySz) == 0; }
    };
    struct KV {
        Key k; int v;
        KV(const Key &K, int V) : k(K), v(V) {}
    };
    typedef vector<KV> KVV; KVV b[HASHB];
    u32 fnv_hash(const Key &k, int len) const {
        uch *p = reinterpret_cast<uch*>(const_cast<int*>(k.n));
        u32 h = 2166136261U;
        for (int i = 0; i < len; ++i) h = (h * 16777619U) ^ p[i];
        return h;
    }
    bool add(const Key &k, u64 &id) {
        int i = fnv_hash(k, KeySz) % HASHB;
        for (int j = 0, J = b[i].size(); j < J; ++j)
            if (b[i][j].k == k) { id = i; id <<= 32; id |= j; return false; }
        b[i].push_back(KV(k, 1));
        id = i; id <<= 32; id |= (b[i].size() - 1);
        return true;
    }
    KV get(u64 id) const { return b[id>>32][id&0xFFFFFFFF]; }
};

//
// Binary Indexed Tree
//
struct Bit {
    int f[MAXBIT + 1]; int n;
    void init(int N) { n=N; Zero(f); }
    void add(int i, int v) { while (i <= n) { f[i] += v; i += GetFS(i); } }
    int query(int i) {
        int r = 0; while (i) { r += f[i]; i -= GetFS(i); } return r; }
};

//
// Segment Tree
//
#define MAXN 1024000
#define MAXH 21  // 1 + ceil(log2(MAXN))
struct SegTree {
    struct Node {
        int v;   // tree value
        bool u;  // requires update
    };

    Node T[1 << MAXH];
    int n;

    void init(int N) { n = N; tree_init(1, 0, n-1); }
    void tree_init(int x, int a, int b) {
        T[x].u = false;
        if (a == b) { T[x].v = 1; return; }
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        tree_init(lt, a, md);
        tree_init(rt, md + 1, b);
        T[x].v = T[lt].v + T[rt].v;
    }

    void propagate(int x, int a, int b) {
        if (! T[x].u) return;
        T[x].v = 0;
        if (a != b) {
            int lt = 2*x, rt = lt + 1;
            T[lt].u = T[rt].u = true;
        }
        T[x].u = false;
    }

    void update(int i, int j, int v) { tree_update(i, j, v, 1, 0, n-1); }
    void tree_update(int i, int j, int v, int x, int a, int b) {
        propagate(x, a, b);
        if (j < a || i > b) return;
        if (a == b) { T[x].v += v; return; }
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        if (a >= i && b <= j) {
            T[x].v += v * (b - a + 1);
            T[lt].u += v;
            T[rt].u += v;
            return;
        }
        tree_update(i, j, v, lt, a, md);
        tree_update(i, j, v, rt, md + 1, b);
        T[x].v = T[rt].v + T[lt].v;
    }

    int query(int i, int j) { return tree_query(i, j, 1, 0, n-1); }
    int tree_query(int i, int j, int x, int a, int b) {
        if (j < a || i > b) return -1;
        propagate(x, a, b);
        if (a >= i && b <= j) return T[x].v;
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        int q1 = tree_query(i, j, lt, a, md);
        int q2 = tree_query(i, j, rt, md + 1, b);
        if (q1 < 0) return q2;
        if (q2 < 0) return q1;
        return A[q1] <= A[q2] ? q1 : q2;
    }
};

//
// Sparse Table
//
struct SpTable {
    IV A; IIV M; int n;
    SpTable(int N) : n(N) {
        A.resize(n); int l = 1 + ceil(log2(n));
        M = IIV(n, IV(l));
    }
    void init() {
        for (int i = 0; i < n; ++i) M[i][0] = i;
        for (int j = 1, p = 2, q = 1; p <= n; ++j, p <<= 1, q <<= 1)
            for (int i = 0; i + p - 1 < n; ++i) {
                int a = M[i][j - 1], b = M[i + q][j - 1];
                M[i][j] = A[a] <= A[b] ? a : b;
            }
    }
    int query_val(int i, int j) { return A[query_idx(i, j)]; }
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
        int p, l, r, s, k;  // parent, left, right, size, key
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
            else                    for (x=T[t].l; T[x].r != Nil; x=T[x].r) ;
            T[t].k = T[x].k;
            t = x;
        }
        if (T[t].l == Nil && T[t].r == Nil) {
            if (T[t].p == Nil) { root = Nil; return; }
            if (PAR(t).l == t) PAR(t).l = Nil;
            else               PAR(t).r = Nil;
        }
        else {
            x = T[t].l != Nil ? T[t].l : T[t].r;
            if (T[t].p == Nil) { T[root = x].p = Nil; return; }
            if (PAR(t).l == t) PAR(t).l = x;
            else               PAR(t).r = x;
            T[x].p = T[t].p;
        }
        for (x = T[t].p; x != Nil; x = T[x].p) --T[x].s;
    }
};

#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;


#define MAXN 100000
#define MAXQ 50000

#define GetFS(b) ((b) & -(b))


typedef unsigned int u32;

typedef vector<int> IV;


//
// I/O
//
#define BUF 524288
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
    char next_char() { skip(); char c = b; read(); return c; }
};

//
// Segment Tree
//
struct SegTree {
    IV A, T;  // T[i]: number of nodes in the tree with root i
    int n;    // number of nodes in tree
    int s;    // number of armies (active nodes)

    SegTree(int N, int S) : n(N), s(S) {
        A.resize(n); int h = 1 + ceil(log2(n)); T.resize(1 << h); }
    void init() { tree_init(1, 0, n - 1); }
    int query(int p) { return tree_query(1, 0, n - 1, p); }
    void update(int idx) { tree_update(1, 0, n - 1, idx); }
    void tree_init(int x, int a, int b) {
        if (a == b) { T[x] = a < s ? 1 : 0; return; }
        int l = 2*x, r = 2*x + 1, m = (a+b)/2;
        tree_init(l, a, m);
        tree_init(r, m + 1, b);
        T[x] = T[l] + T[r];
    }
    int tree_query(int x, int a, int b, int p) {
        if (a == b) {
            --s;
            T[x] = 0;
            return A[a];
        }
        int l = 2*x, r = 2*x + 1, m = (a+b)/2;
        int q;
        if (p <= T[l]) q = tree_query(l, a, m, p);
        else           q = tree_query(r, m + 1, b, p - T[l]);
        T[x] = T[l] + T[r];
        return q;
    }
    void tree_update(int x, int a, int b, int i) {
        if (a == b) {
            T[x] = 1;
            ++s;
            return;
        }
        int l = 2*x, r = 2*x + 1, m = (a+b)/2;
        if (i <= m) tree_update(l, a, m, i);
        else        tree_update(r, m + 1, b, i);
        T[x] = T[l] + T[r];
    }
};


int n, q;


int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();
        q = rr.next_u32();

        int lst = 0;
        SegTree tree(n + q, n);

        for (int i = 0; i < n; ++i)
            tree.A[lst++] = rr.next_u32();

        tree.init();

        printf("Case %d:\n", ++ncase);
        while (q--) {
            char type = rr.next_char();

            if (type == 'a') {
                int p = rr.next_u32();
                tree.update(lst);
                tree.A[lst++] = p;
                ++n;
            }
            else {
                int k = rr.next_u32();
                if (k > tree.s) { puts("none"); continue; }
                printf("%d\n", tree.query(k));
            }
        }
    }

    return 0;
}

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;


#define MAXN 100000


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
};

//
// Segment Tree
//
struct SegTree {
    IV A, M; int n;
    SegTree(int N) : n(N) {
        A.resize(n); int h = 1 + ceil(log2(n)); M.resize(1 << h); }
    void init() { tree_init(1, 0, n - 1); }
    int query_val(int i, int j) { return A[tree_query(1, 0, n - 1, i, j)]; }
    void tree_init(int x, int a, int b) {
        if (a == b) { M[x] = a; return; }
        int l = 2*x, r = 2*x + 1, m = (a+b)/2;
        tree_init(l, a, m);
        tree_init(r, m + 1, b);
        M[x] = A[M[l]] <= A[M[r]] ? M[l] : M[r];
    }
    int tree_query(int x, int a, int b, int i, int j) {
        if (j < a || i > b) return -1;
        if (a >= i && b <= j) return M[x];
        int l = 2*x, r = 2*x + 1, m = (a+b)/2;
        int q1 = tree_query(l, a, m, i, j);
        int q2 = tree_query(r, m + 1, b, i, j);
        if (q1 < 0) return q2;
        if (q2 < 0) return q1;
        return A[q1] <= A[q2] ? q1 : q2;
    }
};


int N, q;
int I, J;


int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        N = rr.next_u32();
        q = rr.next_u32();

        SegTree tree(N);
        for (int i = 0; i < N; ++i)
            tree.A[i] = rr.next_u32();

        printf("Case %d:\n", ++ncase);

        tree.init();

        while (q--) {
            I = rr.next_u32();
            J = rr.next_u32();

            printf("%d\n", tree.query_val(I - 1, J - 1));
        }
    }

    return 0;
}

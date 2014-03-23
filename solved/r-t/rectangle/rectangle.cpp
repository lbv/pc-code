#include <cmath>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;


typedef unsigned int u32;
typedef long long    i64;

typedef pair<int, int> II;
typedef queue<II>      IIQ;
typedef vector<int> IV;
typedef vector<u32> UV;


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
    IV C; UV B;  // C is the array of colors, B the bitmasks of colors
    SegTree(int N) : n(N) {
        A.resize(n);
        C.resize(n);

        int h = 1 + ceil(log2(n));
        M.resize(1 << h);
        B.resize(1 << h);
    }
    void init() { tree_init(1, 0, n - 1); }
    int query_val(int i, int j) { return A[tree_query(1, 0, n - 1, i, j)]; }
    int query_idx(int i, int j) { return tree_query(1, 0, n - 1, i, j); }
    u32 query_col(int i, int j) { return tree_color(1, 0, n - 1, i, j); }
    void tree_init(int x, int a, int b) {
        if (a == b) {
            M[x] = a;
            B[x] = 1 << C[a];
            return;
        }
        int l = 2*x, r = 2*x + 1, m = (a+b)/2;
        tree_init(l, a, m);
        tree_init(r, m + 1, b);
        M[x] = A[M[l]] <= A[M[r]] ? M[l] : M[r];
        B[x] = B[l] | B[r];
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
    u32 tree_color(int x, int a, int b, int i, int j) {
        if (j < a || i > b) return 0;
        if (a >= i && b <= j) return B[x];
        int l = 2*x, r = 2*x + 1, m = (a+b)/2;
        u32 b1 = tree_color(l, a, m, i, j);
        u32 b2 = tree_color(r, m + 1, b, i, j);
        return b1 | b2;
    }
};


int N, C;
u32 full_bitmask;


i64 solve(SegTree &t)
{
    IIQ q;
    q.push(II(0, N - 1));

    i64 ans = 0;
    while (! q.empty()) {
        int i = q.front().first;
        int j = q.front().second;
        q.pop();

        int midx = t.query_idx(i, j);
        u32 bmsk = t.query_col(i, j);

        i64 a = 0;
        if (bmsk == full_bitmask) {
            a = j - i + 1;
            a *= t.A[midx];
        }
        if (a > ans) ans = a;

        if (midx > i)
            q.push(II(i, midx - 1));
        if (midx < j)
            q.push(II(midx + 1, j));
    }

    return ans;
}

int main()
{
    Reader rr;

    while (true) {
        N = rr.next_u32();
        C = rr.next_u32();
        if (N == 0 && C == 0) break;

        full_bitmask = (1 << C) - 1;
        SegTree tree(N);
        for (int i = 0; i < N; ++i)
            tree.A[i] = rr.next_u32();
        for (int i = 0; i < N; ++i)
            tree.C[i] = rr.next_u32();

        tree.init();

        printf("%lld\n", solve(tree));
    }

    return 0;
}

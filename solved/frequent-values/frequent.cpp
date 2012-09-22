#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;


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
    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; b > 32; read()) v = v*10 + b-48; return s ? -v : v; }
};

struct Range {
    int i, j, l;
    Range() { i=j=l=0; }
    Range(int I, int J) : i(I), j(J) { l = j - i + 1; }
    bool operator<(const Range &x) const { return l < x.l; }
};
typedef vector<Range> RV;

//
// Segment Tree
//
struct SegTree {
    int n;
    IV A;
    RV T;   // T[i]: largest range with the same value for tree with root i
    RV R;   // R[i]: range of the value at A[i]
    SegTree(int N) : n(N) {
        A.resize(n); R.resize(n);
        int h = 1 + ceil(log2(n)); T.resize(1 << h); }
    void init() { calc_ranges(); tree_init(1, 0, n - 1); }
    Range query(int i, int j) { return tree_query(1, 0, n - 1, i, j); }
    void tree_init(int x, int a, int b) {
        if (a == b) { T[x] = Range(a, b); return; }
        int l = 2*x, r = 2*x + 1, m = (a+b)/2;
        tree_init(l, a, m);
        tree_init(r, m + 1, b);
        T[x] = T[l] < T[r] ? T[r] : T[l];
        if (A[m] == A[m + 1]) {
            Range r(max(R[m].i, a), min(R[m + 1].j, b));
            if (T[x] < r) T[x] = r;
        }
    }
    Range tree_query(int x, int a, int b, int i, int j) {
        if (j < a || i > b) return Range();
        if (a >= i && b <= j) return T[x];
        int l = 2*x, r = 2*x + 1, m = (a+b)/2;
        Range q1 = tree_query(l, a, m, i, j);
        Range q2 = tree_query(r, m + 1, b, i, j);
        if (q1.l == 0) return q2;
        if (q2.l == 0) return q1;
        Range ans = q1 < q2 ? q2 : q1;
        if (A[m] == A[m + 1]) {
            int from = max(a, i);
            int to   = min(b, j);
            Range r(max(R[m].i, from), min(R[m + 1].j, to));
            if (ans < r) ans = r;
        }
        return ans;
    }
    void calc_ranges() {
        R[0].i = 0;
        for (int i = 1; i < n; ++i)
            R[i].i = A[i] == A[i - 1] ? R[i - 1].i : i;

        R[n - 1].j = n - 1;
        for (int j = n - 2; j >= 0; --j)
            R[j].j = A[j] == A[j + 1] ? R[j + 1].j : j;
    }
};


int n, q;


int main()
{
    Reader rr;

    while (true) {
        n = rr.next_u32();
        if (n == 0) break;
        q = rr.next_u32();

        SegTree tree(n);

        for (int i = 0; i < n; ++i)
            tree.A[i] = rr.next_int();

        tree.init();

        while (q--) {
            int i = rr.next_u32();
            int j = rr.next_u32();

            Range r = tree.query(i - 1, j - 1);
            printf("%d\n", r.l);
        }
    }

    return 0;
}

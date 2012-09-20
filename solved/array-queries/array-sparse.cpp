#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;


#define MAXN 100000


typedef unsigned int u32;

typedef vector<int> IV;
typedef vector<IV>  IIV;


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

        SpTable tab(N);
        for (int i = 0; i < N; ++i)
            tab.A[i] = rr.next_u32();

        printf("Case %d:\n", ++ncase);

        tab.init();

        while (q--) {
            I = rr.next_u32();
            J = rr.next_u32();

            printf("%d\n", tab.query_val(I - 1, J - 1));
        }
    }

    return 0;
}

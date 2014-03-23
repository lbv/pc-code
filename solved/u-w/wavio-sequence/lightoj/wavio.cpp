#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 100000


typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; b > 32; read()) v = v*10 + b-48; return s ? -v : v; }
};


int N;
int seq[MAXN];
int rev[MAXN];

int len_lis[MAXN];
int len_lds[MAXN];

int I[MAXN + 1];


void lis(int *seq, int *ls)
{
    int len = 0;
    for (int i = 0; i < N; ++i) {
        int lo = 1, hi = len;
        while (lo <= hi) {
            int m = (lo + hi) / 2;
            if (I[m] < seq[i]) lo = m + 1;
            else hi = m - 1;
        }
        I[lo] = seq[i], ls[i] = lo;
        if (len < lo) len = lo;
    }
}

int solve()
{
    lis(seq, len_lis);
    lis(rev, len_lds);

    int best = 0;
    for (int i = 0, j = N - 1; i < N; ++i, --j) {
        int wavio = min(len_lis[i], len_lds[j])*2 - 1;
        if (wavio > best) best = wavio;
    }

    return best;
}

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        N = rr.next_u32();
        for (int i = 0, j = N - 1; i < N; ++i, --j)
            seq[i] = rev[j] = rr.next_int();

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}

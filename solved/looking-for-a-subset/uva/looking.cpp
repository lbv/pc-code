#include <cstdio>


#define MAXN 10000

const int NEGINF = -100000000 - 10;


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


int n, q, m;

int rev[MAXN];  // array of integers in reverse order

int len_lds[MAXN];
int I[MAXN + 1];


int lds(int *seq, int *ls)
{
    int len = 0;
    for (int i = 0; i < n; ++i) {
        int lo = 1, hi = len;
        while (lo <= hi) {
            int m = (lo + hi) / 2;
            if (I[m] > seq[i]) lo = m + 1;
            else hi = m - 1;
        }
        I[lo] = seq[i], ls[i] = lo;
        if (len < lo) len = lo;
    }
    return len;
}

void solve()
{
    int last = NEGINF;
    int len = m;

    printf("   ");

    int cnt = 0;
    for (int i = n - 1; len > 0 && i >= 0; --i)
        if (len_lds[i] >= len && rev[i] > last) {
            printf(" %d", rev[i]);
            ++cnt;
            --len;
            last = rev[i];
        }

    if (cnt == 0)
        puts(" Impossible");
    else
        putchar('\n');
}

int main()
{
    Reader rr;

    int ncase = 0;
    while (true) {
        n = rr.next_u32();
        q = rr.next_u32();

        if (n == 0) break;

        for (int i = n - 1; i >= 0; --i)
            rev[i] = rr.next_int();

        printf("Set %d:\n", ++ncase);
        lds(rev, len_lds);

        for (int ss = 1; ss <= q; ++ss) {
            printf("  Subset %d:\n", ss);
            m = rr.next_u32();
            solve();
        }
    }

    return 0;
}

#include <cstdio>


#define MAXLEN 1000000


typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
    void next(char *s, int &l) {
        l = 0; for (skip(); b > 32; read()) *s++ = b, ++l; *s = 0; }
};

#define MAXS MAXLEN
#define MAXW MAXLEN
struct KMP {
    char S[MAXS + 1], W[MAXW + 1]; int ls, lw; int T[MAXW + 1];
    void init() {
        T[0] = -1, T[1] = 0;
        for (int p = 2, c = 0; p < lw;) {
            if (W[p-1] == W[c]) T[p++] = ++c;
            else if (c > 0) c = T[c];
            else T[p++] = 0;
        }
    }
    void search(int &sz) {
        sz = 0;
        for (int m=0, i=0; m + i < ls;) {
            if (W[i] == S[m + i]) {
                if (++i > sz) sz = i;
            }
            else { m += i - T[i]; i = T[i] >= 0 ? T[i] : 0; }
        }
    }
};


KMP kmp;


void solve()
{
    for (int i = 0, j = kmp.lw - 1; i < kmp.lw; ++i, --j) kmp.S[j] = kmp.W[i];
    kmp.S[kmp.ls = kmp.lw] = 0;

    kmp.init();
    int sz;
    kmp.search(sz);

    for (int i = sz - 1; i >= 0; --i)
        putchar(kmp.W[i]);
    putchar('\n');
}

int main()
{
    Reader rr;
    int T = rr.next_u32();
    while (T--) {
        rr.next(kmp.W, kmp.lw);
        solve();
    }

    return 0;
}

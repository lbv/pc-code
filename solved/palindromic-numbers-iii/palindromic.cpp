#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXDIG 100000

typedef unsigned int u32;

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
    void next(char *s, int &l) {
        l = 0;
        for (skip(); b > 32; read()) {
            *s++ = b;
            ++l;
        }
        *s = 0;
    }
};

char n[MAXDIG + 2];
int nlen;

bool c;  // carry

void solve()
{
    c = true;

    for (int i = 0, j = nlen - 1; j >= 0; --j, ++i) {
        if (c) {
            if (n[j] == '9') {
                c = true;
                n[j] = '0';
            }
            else {
                c = false;
                ++n[j];
            }
        }

        if (i <= j) {
            if (n[i] < n[j])
                c = true;
            n[j] = n[i];
        }
        else {
            n[i] = n[j];
        }
    }

    if (c) n[nlen - 1] = '1';
}

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        rr.next(n, nlen);
        solve();
        printf("Case %d: %s%s\n", ++ncase, c ? "1" : "", n);
    }

    return 0;
}

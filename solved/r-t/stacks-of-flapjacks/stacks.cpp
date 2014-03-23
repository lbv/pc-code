#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXLINE  25
#define MAXSTACK 30


typedef unsigned int u32;


#define BUF 256
struct LineReader {
    char buf[BUF]; char b; int bi, bz;
    bool read_line() {
        bi = 0; bool r; if (gets(buf)) r = (bz = strlen(buf)) > 0;
        else r = false, bz = 0; read(); return r; }
    void read() { b = bi < bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    bool has_next() { skip(); return b > 0; }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};


char line[256];
int len;

int stk[MAXSTACK];
int sz;


void flip(int end)
{
    for (int i = 0, j = end; i < j; ++i, --j)
        swap(stk[i], stk[j]);
    printf("%d ", sz - end);
}

void solve()
{
    for (int i = sz - 1; i >= 0; --i) {
        int ld = stk[0];  // diameter of largest pancake
        int li = 0;       // index of largest pancake

        for (int j = 1; j <= i; ++j)
            if (stk[j] > ld) ld = stk[j], li = j;

        if (li == i) continue;

        if (li != 0)
            flip(li);

        flip(i);
    }

    puts("0");
}

int main()
{
    LineReader lr;

    while (lr.read_line()) {
        sz = 0;

        while (lr.has_next())
            stk[sz++] = lr.next_u32();

        printf("%d", stk[0]);
        for (int i = 1; i < sz; ++i)
            printf(" %d", stk[i]);
        putchar('\n');

        solve();
    }

    return 0;
}

#include <cstdio>

typedef unsigned int u32;
typedef long long i64;

#define MAXN 100000
#define SC(t,v) static_cast<t>(v)

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 nextU32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

int a[MAXN];

int main()
{
    Reader rr;
    u32 T = rr.nextU32();;

    int ncase = 1;
    while (T--) {
        int n = rr.nextU32();
        int q = rr.nextU32();

        i64 val = 0;

        for (int i = 0, j = n - 1; i < n; i++, j--) {
            a[i] = rr.nextU32();
            val += SC(i64, a[i]) * (j - i);
        }

        printf("Case %d:\n", ncase++);

        while (q--) {
            int comm = rr.nextU32();
            if (comm == 1) {
                printf("%lld\n", val);
                continue;
            }
            int x = rr.nextU32();
            int v = rr.nextU32();
            int y = n - 1 - x;
            val -= SC(i64, a[x]) * (y - x);
            a[x] = v;
            val += SC(i64, a[x]) * (y - x);
        }
    }

    return 0;
}

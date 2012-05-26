#include <cstdio>

typedef unsigned int u32;
#define BUF 65536
class Reader {
    char buf[BUF]; char b; int bi, bz;
public:
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 nextU32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

u32 n, k, i, d;

int main(void)
{
    Reader _r;
    n = _r.nextU32();
    k = _r.nextU32();
    d = 0;
    while (n--) {
        i = _r.nextU32();
        if (i % k == 0) d++;
    }
    printf ("%d\n", d);

    return 0;
}

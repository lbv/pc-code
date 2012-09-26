#include <cstdio>

typedef unsigned int u32;

struct Reader {
    char b;
    Reader() { read(); }
    void read() { int r = fgetc_unlocked(stdin); b = r == EOF ? 0 : r; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

u32 n, k, i, d;

int main(void)
{
    Reader rr;

    n = rr.next_u32();
    k = rr.next_u32();
    d = 0;
    while (n--) {
        i = rr.next_u32();
        if (i % k == 0) d++;
    }
    printf ("%d\n", d);

    return 0;
}

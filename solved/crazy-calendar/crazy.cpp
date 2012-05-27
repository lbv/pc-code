#include <cstdio>

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
    // Optional methods
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        int R = rr.next_u32();
        int C = rr.next_u32();

        int nim = 0;
        int coins;

        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j) {
                coins = rr.next_u32();

                int dis = (R-1-i) + (C-1-j);
                if (dis & 1)
                    nim ^= coins;
            }

        printf("Case %d: %s\n", ++ncase, nim == 0 ? "lose" : "win");
    }

    return 0;
}

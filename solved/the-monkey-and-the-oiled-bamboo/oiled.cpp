#include <cstdio>

typedef unsigned int u32;


//
// I/O
//
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
};


int n;

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();

        int max_k = 0;
        int cur_k = 0;
        int prev  = 0;

        while (n--) {
            int r = rr.next_u32();

            int dist = r - prev;
            prev = r;

            if (dist > max_k) {
                max_k = dist;
                cur_k = max_k - 1;
                continue;
            }

            if (dist < cur_k) continue;
            if (dist == cur_k) {
                --cur_k;
                continue;
            }

            max_k = cur_k = max_k + 1;
        }

        printf("Case %d: %d\n", ++ncase, max_k);
    }

    return 0;
}

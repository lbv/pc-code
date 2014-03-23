#include <cstdio>


typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
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
        int dist;

        while (n--) {
            int cur = rr.next_u32();
            dist = cur - prev;
            prev = cur;

            if (dist < cur_k) continue;

            if (dist == cur_k) {
                --cur_k;
                continue;
            }

            if (dist > max_k) {
                max_k = dist;
                cur_k = max_k - 1;
                continue;
            }

            max_k = cur_k = max_k + 1;
        }

        printf("Case %d: %d\n", ++ncase, max_k);
    }

    return 0;
}

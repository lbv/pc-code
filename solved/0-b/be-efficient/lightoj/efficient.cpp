#include <cstdio>
#include <cstring>


#define MAXM 100000

#define Zero(v) memset((v), 0, sizeof(v))


typedef unsigned int u32;
typedef long long    i64;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};


int N, M;

// cmod[m]: count of occurrences when the modulo of the sequence is m
int cmod[MAXM];


int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        N = rr.next_u32();
        M = rr.next_u32();

        Zero(cmod);
        cmod[0] = 1;

        i64 ans = 0;
        int m = 0;

        while (N--) {
            int num = rr.next_u32();
            m = (m + num) % M;

            ans += cmod[m];
            ++cmod[m];
        }

        printf("Case %d: %lld\n", ++ncase, ans);
    }

    return 0;
}

#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;

#define MAXN 5000000

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

u64 scores[MAXN + 1];

// Number Theory
#define ISCOMP(n)  (_c[(n)>>5]&(1<<((n)&31)))
#define SETCOMP(n) _c[(n)>>5]|=(1<<((n)&31))
namespace Num
{
    const int MAX = 5000000; // 5*10^6
    const int LMT = 2237;    // sqrt(MAX)
    int _c[(MAX>>5)+1];

#define ScoreCycle(v) \
    for (int _i=v; _i <= MAX; _i+=v) \
        scores[_i] = (scores[_i] / v) * (v-1);

    // Modified to calculate the values in scores[]
    void primeSieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!ISCOMP(i)) for (int j = i*i; j <= MAX; j+=i+i) SETCOMP(j);

        ScoreCycle(2);
        for (int i=3; i <= MAX; i+=2)
            if (!ISCOMP(i))
                ScoreCycle(i);
    }
}


void prepare()
{
    scores[0] = scores[1] = 0;
    for (int i = 2; i <= MAXN; i++) scores[i] = i;

    Num::primeSieve();

    for (int i = 2; i <= MAXN; i++)
        scores[i] = scores[i-1] + scores[i]*scores[i];
}

int main()
{
    prepare();

    Reader rr;
    u32 T = rr.nextU32();

    int ncase = 1;
    while (T--) {
        u32 a = rr.nextU32();
        u32 b = rr.nextU32();

        printf("Case %d: %llu\n", ncase++, scores[b] - scores[a-1]);
    }

    return 0;
}

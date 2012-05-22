#include <cstdio>

typedef unsigned long long u64;
typedef unsigned int       u32;

#define MAXN 3000000

#define Sc(t,v) static_cast<t>(v)

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
    u32 nextU32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

namespace Num {
    void eulerPhi(int a[], int N) {
        for (int i = 1; i <= N; i += 2) a[i] = i;
        for (int i = 2; i <= N; i += 2) a[i] = i/2;
        for (int i = 3; i <= N; i += 2)
            if (a[i] == i) {
                a[i]--;
                for (int j = i+i; j <= N; j += i) a[j] -= a[j]/i;
            }
    }
}
using namespace Num;

int phi[MAXN + 1];
u64 val[MAXN + 1];  // used for various calculations

void prepare()
{
    // Calculate the values of phi(x) up to MAXN
    eulerPhi(phi, MAXN);

    // Calculate the values of Sum_{d|i}{ d * phi(d) } for each i
    for (int i = 1; i <= MAXN; i++) val[i] = 1;
    for (int i = 2; i <= MAXN; i++)
        for (int j = i; j <= MAXN; j += i)
            val[j] += Sc(u64, phi[i]) * i;

    // Calculate the values of Sum{ LCM(n,k): k = 1, 2, 3, .., n-1 }
    for (int i = 1; i <= MAXN; i++)
        val[i] = (val[i] - 1)/2 * i;

    // Finally, calculate all pairs LCMs
    for (int i = 1; i <= MAXN; i++)
        val[i] += val[i-1];
}

int main()
{
    prepare();

    Reader rr;
    int T = rr.nextU32();

    int ncase = 1;
    while (T--) {
        u32 n = rr.nextU32();
        printf("Case %d: %llu\n", ncase++, val[n]);
    }

    return 0;
}

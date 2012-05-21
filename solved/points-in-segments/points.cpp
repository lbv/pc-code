#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef unsigned int u32;
typedef vector<int>  IV;

#define Sc(t,v) static_cast<t>(v)
#define Iter(t,v)  t::iterator v

#define MAXN 100000

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

int main()
{
    Reader rr;
    int T = rr.nextU32();

    int ncase = 1;
    while (T--) {
        int n = rr.nextU32();
        int q = rr.nextU32();

        IV ns;
        while (n--)
            ns.push_back(rr.nextU32());

        printf("Case %d:\n", ncase++);
        while (q--) {
            int A = rr.nextU32();
            int B = rr.nextU32();

            Iter(IV, lo) = lower_bound(ns.begin(), ns.end(), A);
            Iter(IV, hi) = upper_bound(ns.begin(), ns.end(), B);

            printf("%d\n", Sc(int, hi-lo));
        }
    }

    return 0;
}

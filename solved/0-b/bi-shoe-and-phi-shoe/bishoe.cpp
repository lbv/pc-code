#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long    i64;
typedef unsigned int u32;

typedef vector<int>        IV;
typedef IV::const_iterator IVci;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)

// I/O
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

// Number Theory
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
namespace Num
{
    const int MAX = 1000003;  // includes one prime over 10^6
    const int LMT =    1001;  // sqrt(MAX)
    int _c[(MAX>>6)+1];
    IV primes;
    void primeSieve() {
        for (int i = 3; i <= LMT; i += 2)
            if (!IsComp(i)) for (int j = i*i; j <= MAX; j+=i+i) SetComp(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!IsComp(i)) primes.push_back(i);
    }
}
using namespace Num;

int main()
{
    primeSieve();

    Reader rr;
    int T = rr.next_u32();

    int ncase = 1;
    while (T--) {
        int n = rr.next_u32();

        IV ns;

        while (n--) {
            int x = rr.next_u32();
            ns.push_back(x);
        }

        sort(ns.begin(), ns.end());

        i64 xukha = 0;
        IVci p = primes.begin();
        cFor (IV, num, ns) {
            while (*num >= *p) p++;
            xukha += *p;
        }

        printf("Case %d: %lld Xukha\n", ncase++, xukha);
    }

    return 0;
}

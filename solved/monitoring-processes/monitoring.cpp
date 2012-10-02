#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 50000


typedef unsigned int u32;


struct Reader {
    char b; Reader() { read(); }
    void read() { int r = fgetc_unlocked(stdin); b = r == EOF ? 0 : r; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

struct Point {
    int n, t;  // number and type (0: process start, 1: process end)
    Point() {}
    Point (int N, int T) : n(N), t(T) {}
    bool operator<(const Point &x) const {
        if (n != x.n) return n < x.n;
        return t < x.t;
    }
};


int n;
Point pts[2*MAXN];
int np;


int solve()
{
    sort(pts, pts + np);

    int t = 0;  // total number of wrappers
    int f = 0;  // free wrappers
    for (int i = 0; i < np; ++i) {
        if (pts[i].t == 1) ++f;
        else {
            if (f == 0) ++t;
            else --f;
        }
    }
    return t;
}

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();
        np = 0;
        for (int i = 0; i < n; ++i) {
            int t = rr.next_u32();
            pts[np++] = Point(t, 0);
            t = rr.next_u32();
            pts[np++] = Point(t, 1);
        }


        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}

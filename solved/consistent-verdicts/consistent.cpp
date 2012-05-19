#include <algorithm>
#include <cstdio>
using namespace std;

typedef unsigned int u32;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

#define MAXN 700

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

struct Point {
    int x, y;
    Point(int X, int Y) : x(X), y(Y) {}
    Point() {}
    int dist(const Point &p) const {
        int dx = x - p.x;
        int dy = y - p.y;
        return dx*dx + dy*dy;
    }
};

Point ps[MAXN];
int ds[MAXN * MAXN];

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        int N = rr.next_u32();

        for (int i = 0; i < N; ++i) {
            ps[i].x = rr.next_u32();
            ps[i].y = rr.next_u32();
        }

        int n_ds = 0;
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
                ds[n_ds++] = ps[i].dist(ps[j]);

        sort(ds, ds + n_ds);

        int prev = 0;
        int n = 1;

        for (int i = 0; i < n_ds; ++i)
            if (ds[i] > prev) {
                prev = ds[i];
                ++n;
            }

        printf("Case %d: %d\n", ++ncase, n);
    }

    return 0;
}

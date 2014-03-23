#include <algorithm>
#include <cmath>
#include <cstdio>
#include <utility>
using namespace std;


#define MAXN 50000
#define MAXQ 50000


typedef unsigned int u32;

typedef pair<int, int> II;


//
// I/O
//
struct Reader {
    char b; Reader() { read(); }
    void read() { int r = fgetc_unlocked(stdin); b = r == EOF ? 0 : r; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

struct Point {
    int x, q;  // coordinate, query number
    int t;     // 0 if first point of segment, 1 if query point, 2 if second point
    Point() {}
    Point(int X, int Q, int T) : x(X), q(Q), t(T) {}
    bool operator<(const Point &p) const {
        if (x != p.x) return x < p.x;
        return t < p.t;
    }
};



int n, q;

Point pts[2*MAXN + MAXQ];
II answers[MAXQ];
int np;


int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();
        q = rr.next_u32();

        np = 0;
        for (int i = 0; i < n; ++i) {
            int a = rr.next_u32();
            int b = rr.next_u32();

            pts[np++] = Point(a, 0, 0);
            pts[np++] = Point(b, 0, 2);
        }

        for (int i = 0; i < q; ++i) {
            int a = rr.next_u32();

            pts[np++] = Point(a, i, 1);
        }

        sort(pts, pts + np);

        int seg = 0;  // count of segments

        int nq = 0;
        for (int i = 0; i < np; ++i) {
            if (pts[i].t == 0) ++seg;
            else if (pts[i].t == 2) --seg;
            else
                answers[nq++] = II(pts[i].q, seg);
        }

        sort(answers, answers + nq);

        printf("Case %d:\n", ++ncase);
        for (int i = 0; i < nq; ++i)
            printf("%d\n", answers[i].second);
    }

    return 0;
}

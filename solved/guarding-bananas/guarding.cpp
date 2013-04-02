#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;


#define MAXN 100000


const double Pi = acos(-1);


typedef unsigned int u32;
typedef long long    i64;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; b > 32; read()) v = v*10 + b-48; return s ? -v : v; }
};

template <typename T>
struct Point {
    T x, y;
    Point() { x=y=0; }
    bool operator<(const Point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
    bool operator==(const Point &p) const { return x == p.x && y == p.y; }

    // cross product magnitude of axb, relative to this
    T cross(const Point &a, const Point &b) const {
        return (a.x-x)*(b.y-y) - (a.y-y)*(b.x-x);
    }
};
typedef Point<i64> IP;

void convex_hull(IP *p, int n, IP *h, int &k) {
    // Post-cond: n > 1 => h[0] == h[k-1]
    k = 0;
    sort(p, p + n);
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && h[k-2].cross(h[k-1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
    for (int i = n-2, t=k+1; i >= 0; --i) {
        while (k >= t && h[k-2].cross(h[k-1], p[i]) <= 0) k--;
        h[k++] = p[i];
    }
}


int n;

IP pts[MAXN];
IP hull[2*MAXN];


double get_angle(const IP &p1, const IP &p2, const IP &p3)
{
    if (p2 == p3) return 0.0;

    i64 x1 = p2.x - p1.x, y1 = p2.y - p1.y;
    i64 x2 = p3.x - p1.x, y2 = p3.y - p1.y;

    double dot = x1 * x2 + y1 * y2;
    double n1  = sqrt(x1*x1 + y1*y1);
    double n2  = sqrt(x2*x2 + y2*y2);

    double cosa = dot / (n1 * n2);
    if (cosa < -1) cosa = -1;
    else if (cosa > 1) cosa = 1;

    double a = acos(cosa);
    return a/Pi * 180;
}

double solve()
{
    if (n < 3) return 0.0;

    int k;
    convex_hull(pts, n, hull, k);
    if (k < 3) return 0.0;

    double best_ang = 360;
    for (int i = 1, I = k - 1; i < I; ++i) {
        double ang = get_angle(hull[i], hull[i-1], hull[i+1]);
        if (ang < best_ang) best_ang = ang;
    }
    double ang = get_angle(hull[0], hull[1], hull[k - 2]);
    if (ang < best_ang) best_ang = ang;
    return best_ang;
}

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();
        for (int i = 0; i < n; ++i) {
            pts[i].x = rr.next_int();
            pts[i].y = rr.next_int();
        }

        printf("Case %d: %.9lf\n", ++ncase, solve());
    }

    return 0;
}

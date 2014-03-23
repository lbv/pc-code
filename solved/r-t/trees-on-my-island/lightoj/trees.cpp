#include <cstdio>
#include <cstdlib>


#define MAXN 10000


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
    Point(T X, T Y) : x(X), y(Y) {}
    T distance(const Point &p) {
        T dx = p.x - x, dy = p.y - y; return sqrt(dx*dx + dy*dy);
    }
    bool operator<(const Point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
    Point operator-(const Point &b) const { return Point(x - b.x, y - b.y); }
    bool collinear(const Point &b, const Point &c) const {
        return (b.y - y) * (c.x - x) == (c.y - y) * (b.x - x);
    }
};

// area of a polygon, times two
template <typename T>
T poly_area2(Point<T> *p, int n)
{
    T a = 0;
    for (int i = 0, j = n - 1; i < n; j = i++)
        a += (p[j].x + p[i].x) * (p[j].y - p[i].y);
    if (a < 0) a *= -1;
    return a;
}

template <typename T>
T lattice_pts(Point<T> &a, Point<T> &b)
{
    if (a.x == b.x) return llabs(a.y - b.y) + 1;
    return gcd(llabs(a.y - b.y), llabs(a.x - b.x)) + 1;
}

template<typename T>
T gcd(T a, T b) { for (T c = a%b; c != 0; a=b,b=c,c=a%b); return b; }


int N;
Point<i64> pts[MAXN];


i64 solve()
{
    i64 a2 = poly_area2(pts, N);  // area
    i64 b  = 0;                   // points in the boundaries of the polygon

    for (int i = 0, j = N - 1; i < N; j = i++)
        b += lattice_pts(pts[i], pts[j]) - 1;

    return (a2 + 2 - b) / 2;
}

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        N = rr.next_u32();
        for (int i = 0; i < N; ++i) {
            int x = rr.next_int();
            int y = rr.next_int();
            pts[i] = Point<i64>(x, y);
        }
        printf("Case %d: %lld\n", ++ncase, solve());
    }

    return 0;
}

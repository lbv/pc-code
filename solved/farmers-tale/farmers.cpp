#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;


#define MAXN 100


template<typename T>
T gcd(T a, T b) { for (T c = a%b; c != 0; a=b,b=c,c=a%b); return b; }

template <typename T>
struct Point {
    T x, y;
    Point() { x=y=0; }
    Point(T X, T Y) : x(X), y(Y) {}
};

template <typename T>
struct Line {
    T a, b, c;  // ax + by + c = 0
    Line() {}
    Line(T A, T B, T C) : a(A), b(B), c(C) {}
    Line(const Point<T> &p1, const Point<T> &p2) {
        if (p1.x == p2.x) { a = 1, b = 0, c = -p1.x; return; }
        a = p1.y-p2.y; b = p2.x-p1.x; c = -a*p1.x - b*p1.y;
    }
    Line(const Point<T> &p, T m) { a = -m; b = 1; c = m*p.x - p.y; }

    bool is_vertical() const { return b == 0; }
    bool is_parallel(const Line &l) const { return a * l.b == b * l.a; }
    bool operator==(const Line &l) const {
        return is_parallel(l) && a * l.c == c * l.a;
    }
};

template<typename T>
struct Fraction {
    T p, q;

    Fraction() : p(0), q(1) {}
    Fraction(T P) : p(P), q(1) {}
    Fraction(T P, T Q) : p(P), q(Q) { simplify(); }
    void simplify() {
        T g = gcd(p, q);
        p /= g;
        q /= g;
    }
    bool operator<(const Fraction &f) const { return p*f.q < q*f.p; }
    bool operator>(const Fraction &f) const { return p*f.q > q*f.p; }
};


typedef Fraction<int> IF;
typedef pair<IF, IF>  FF;


int n, L, W;

Point<int> seg[MAXN][2];
Line<int>  lines[MAXN];



bool intersection(const Line<int> &l1, const Line<int> &l2, Point<IF> &p)
{
    if (l1.is_parallel(l2)) return false;
    const Line<int> &rl = l1.is_vertical() ? l2 : l1;
    int A = l2.b*l1.c - l1.b*l2.c;
    int B = l2.a*l1.b - l1.a*l2.b;
    p.x = IF(A, B);
    p.y = IF(-A*rl.a - B*rl.c, B*rl.b);
    return true;
}

int solve()
{
    IF lox(0);
    IF hix(L);
    IF loy(0);
    IF hiy(W);

    int parts = 1;
    for (int i = 0; i < n; ++i) {
        set<FF> ipts;
        for (int j = 0; j < i; ++j) {
            Point<IF> p;
            if (! intersection(lines[i], lines[j], p)) continue;
            if (p.x > lox && p.x < hix && p.y > loy && p.y < hiy)
                ipts.insert(FF(p.x, p.y));
        }
        parts += ipts.size() + 1;
    }

    return parts;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d", &n, &L, &W);
        for (int i = 0; i < n; ++i) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            seg[i][0] = Point<int>(x1, y1);
            seg[i][1] = Point<int>(x2, y2);
            lines[i] = Line<int>(seg[i][0], seg[i][1]);
        }
        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}

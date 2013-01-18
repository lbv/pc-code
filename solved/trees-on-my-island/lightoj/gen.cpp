#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;


#if 1
#define MAXT      100
#define MAXN      10000
#define MINX     -1000000
#define MAXX      1000000
#define EXTRA_NL  0
#endif

#if 0
#define MAXT      20
#define MAXN      16
#define MINX      0
#define MAXX      20
#define EXTRA_NL  1
#endif

const int    XRange = MAXX - MINX + 1;
const double Pi2    = acos(-1) * 2;


typedef pair<int, int> II;


double cx, cy;

double circle_angle(double a) { return a >= 0 ? a : Pi2 + a; }


struct Pt {
    int x, y;
    Pt() {}
    Pt(int X, int Y) : x(X), y(Y) {}
    bool operator<(const Pt &b) const {
        double a1 = atan2(cy - y, cx - x);
        double a2 = atan2(cy - b.y, cx - b.x);
        return a1 < a2;
    }
};
Pt pts[MAXN];




void test_case(bool crit = false)
{
    int N = crit ? MAXN : rand() % (MAXN - 2) + 3;

#if EXTRA_NL
    puts("");
#endif
    printf("%d\n", N);

    set<II> s;
    cx = cy = 0.0;
    for (int i = 0; i < N; ++i) {
        int x, y;
        do {
            x = rand() % XRange + MINX;
            y = rand() % XRange + MINX;
        } while (s.find(II(x, y)) != s.end());
        s.insert(II(x, y));

        pts[i] = Pt(x, y);
        cx += x;
        cy += y;
    }
    cx /= 1.0 * N;
    cy /= 1.0 * N;

    sort(pts, pts + N);
    for (int i = 0; i < N; ++i)
        printf("%d %d\n", pts[i].x, pts[i].y);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    test_case(true); --T;
    while (T--) test_case();

    return 0;
}

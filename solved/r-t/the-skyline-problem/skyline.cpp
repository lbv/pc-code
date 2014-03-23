#include <cstdio>
#include <set>
using namespace std;

struct Point {
    int  x;  // X-coordinate
    int  h;  // height
    bool l;  // is the left side of the building or not?
    Point(int X, int H, bool L) : x(X), h(H), l(L) {}
    bool operator<(const Point &p) const {
        if (x != p.x) return x < p.x;
        if (l != p.l) return l;
        return h < p.h;
    }
};

typedef multiset<Point> PS;
typedef multiset<int>   IS;

PS pts;

int main()
{
    int L, H, R;

    while (true) {
        if (scanf("%d%d%d", &L, &H, &R) != 3) break;
        pts.insert(Point(L, H, true));
        pts.insert(Point(R, H, false));
    }

    int X = 0;
    H = 0;

    int last_X = pts.begin()->x;
    printf("%d", last_X);

    IS hs;  // heights of buildings being intersected by the sweep-line

    while (! pts.empty()) {
        Point p = *(pts.begin());
        pts.erase(pts.begin());

        int pre_H = H;

        X = p.x;

        if (p.l)
            hs.insert(p.h);
        else
            hs.erase(hs.find(p.h));

        if (hs.size() > 0)
            H = *(hs.rbegin());
        else
            H = 0;

        if (X != last_X && H != pre_H) {
            printf(" %d %d", pre_H, X);
            last_X = X;
        }
    }

    if (X != last_X)
        printf(" %d %d", H, X);

    puts(" 0");

    return 0;
}

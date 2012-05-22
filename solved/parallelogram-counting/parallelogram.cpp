#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef unsigned long long u64;

typedef int p_t;
struct Point {
    p_t x, y;
    Point() { x=y=0; }
    Point(p_t X, p_t Y) : x(X), y(Y) {}
    bool operator<(const Point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
    bool operator==(const Point &p) const {
        return x == p.x && y == p.y;
    }
    Point operator+(const Point &b) const { return Point(x + b.x, y + b.y); }
};

typedef vector<Point> PV;

PV points;
PV pairs;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int n;
        scanf("%d", &n);

        int x, y;
        points.clear();
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &x, &y);
            points.push_back(Point(x, y));
        }

        pairs.clear();
        for (int i = 0, I = n - 1; i < I; ++i)
            for (int j = i + 1; j < n; ++j)
                pairs.push_back(points[i] + points[j]);

        sort(pairs.begin(), pairs.end());

        u64 total = 0;
        u64 cnt = 1;
        for (int i = 1, I = pairs.size(); i < I; ++i) {
            if (pairs[i] == pairs[i-1]) ++cnt;
            else {
                total += cnt*(cnt-1)/2;
                cnt = 1;
            }
        }
        total += cnt*(cnt-1)/2;

        printf("Case %d: %llu\n", ++ncase, total);
    }

    return 0;
}

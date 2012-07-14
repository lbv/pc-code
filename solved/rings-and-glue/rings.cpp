#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;


#define MAXN 100
#define EPS  (1e-9)


typedef vector<int> IV;


// Union-Find disjoint set
struct Set {
    IV s;
    Set(int n) { for (int i=0; i <= n; ++i) s.push_back(i); }
    int find(int i) { if (s[i] == i) return i; return s[i]=find(s[i]); }
    void merge(int i, int j) { s[find(i)] = find(j); }
};


bool eps_less(double a, double b) { return b - a > EPS; }


struct Circle {
    double x, y, r;
    Circle() {}
    Circle(double X, double Y, double R) : x(X), y(Y), r(R) {}

    bool perimeters_touch(const Circle &c) const {
        double dx = x - c.x;
        double dy = y - c.y;
        double dist = sqrt(dx*dx + dy*dy);
        return ! (eps_less(r + c.r, dist) ||
                  eps_less(dist, fabs(r - c.r)));
    }
};


Circle cs[MAXN];
int ss[MAXN];    // set sizes
int n;


int solve()
{
    Set s(n);
    for (int i = 0; i < n; ++i)
        ss[i] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < n; ++j) {
            int u = s.find(i);
            int v = s.find(j);

            if (u != v && cs[i].perimeters_touch(cs[j])) {
                s.merge(u, v);
                int w = s.find(i);
                ss[w] = ss[u] + ss[v];
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i)
        if (ss[i] > ans) ans = ss[i];

    return ans;
}

int main()
{
    while (true) {
        scanf("%d", &n);
        if (n < 0) break;

        for (int i = 0; i < n; ++i) {
            double x, y, r;
            scanf("%lf%lf%lf", &x, &y, &r);
            cs[i] = Circle(x, y, r);
        }

        int ans = solve();
        printf("The largest component contains %d ring%s.\n",
               ans, ans == 1 ? "" : "s");
    }

    return 0;
}

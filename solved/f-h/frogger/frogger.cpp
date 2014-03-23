#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;


#define MAXN 200
#define INF  2000.0


typedef double p_t;
struct Point {
    p_t x, y;
    Point() { x=y=0; }
    Point(p_t X, p_t Y) : x(X), y(Y) {}
    p_t distance(const Point &p) {
        p_t dx = p.x - x, dy = p.y - y; return sqrt(dx*dx + dy*dy);
    }
};


int n;
Point pts[MAXN];
double g[MAXN][MAXN];


void init_graph()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            g[i][j] = i == j ? 0.0 : INF;
}

void floyd()
{
    for (int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                double t = max(g[i][k], g[k][j]);
                g[i][j] = min(g[i][j], t);
            }
}

int main()
{
    int ncase = 0;
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        for (int i = 0; i < n; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            pts[i] = Point(x, y);
        }

        init_graph();
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                g[i][j] = g[j][i] = pts[i].distance(pts[j]);

        floyd();

        printf("Scenario #%d\n", ++ncase);
        printf("Frog Distance = %.3lf\n\n", g[0][1]);
    }

    return 0;
}

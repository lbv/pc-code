#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <map>
using namespace std;


#define MAXT 125
#define MAXN 100
#define MINCOORD -10000
#define MAXCOORD 10000

const int CoordRange = MAXCOORD - MINCOORD + 1;

int pts[2*MAXN][2];

bool collinear(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return (y2 - y1) * (x3 - x1) == (y3 - y1) * (x2 - x1);
}

void test_case()
{
    int n = rand() % MAXN + 1;

    int x = rand() % CoordRange + MINCOORD;
    int y = rand() % CoordRange + MINCOORD;

    printf("\n%d %d %d\n", n, x, y);

    int minpts = n + 1;
    int maxpts = 2*n + 1;

    int npts = rand() % (maxpts - minpts + 1) + minpts;
    for (int i = 0; i < npts; ++i) {
        pts[i][0] = rand() % CoordRange + MINCOORD;
        pts[i][1] = rand() % CoordRange + MINCOORD;
    }

    for (int i = 0; i < n; ++i) {
        int u, v;
        do {
            u = rand() % npts;
            v = rand() % npts;
        } while (u == v ||
                 collinear(x, y, pts[u][0], pts[u][1], pts[v][0], pts[v][1]));

        printf("%d %d %d %d\n", pts[u][0], pts[u][1], pts[v][0], pts[v][1]);
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

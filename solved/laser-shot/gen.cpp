#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;


#if 0
#define MAXT 30
#define MAXN 700
#define MINX -10000
#define MAXX 10000
#endif

#if 1
#define MAXT 30
#define MAXN 700
#define MINX -100
#define MAXX 100
#endif


const int RangeX = MAXX - MINX + 1;


typedef pair<int, int> II;


void test_case(bool crit = false)
{
    int n = crit ? MAXN : rand() % MAXN + 1;
    printf("%d\n", n);

    set<II> pts;
    for (int i = 0; i < n; ++i) {
        int x, y;
        do {
            x = rand() % RangeX + MINX;
            y = rand() % RangeX + MINX;
        } while (pts.find(II(x, y)) != pts.end());

        pts.insert(II(x, y));
        printf("%d %d\n", x, y);
    }
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

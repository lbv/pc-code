#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#if 0
#define MAXC 20
#define MAXN 10000
#define MAXT 10000
#define MAXM 10000
#define MAXA 100000
#endif

#if 1
#define MAXC 20
#define MAXN 5
#define MAXT 30
#define MAXM 12
#define MAXA 100
#endif


#define Zero(v) memset((v), 0, sizeof(v))


bool vis[MAXA + 1];
int ts[MAXM];


void test_case()
{
    int n = rand() % MAXN + 1;
    int t = rand() % MAXT + 1;
    int m = rand() % MAXM + 1;

    printf("%d %d %d\n", n, t, m);
    Zero(vis);
    for (int i = 0; i < m; ++i) {
        int tm;
        do {
            tm = rand() % (MAXA + 1);
        } while (vis[tm]);
        vis[tm] = true;
        ts[i] = tm;
    }

    sort(ts, ts + m);

    for (int i = 0; i < m; ++i) {
        printf("%d %s\n", ts[i], rand() % 2 == 0 ? "left" : "right");
    }
}

int main()
{
    srand(time(NULL));

    int C = MAXC;
    printf("%d\n", C);

    while (C--) test_case();

    return 0;
}

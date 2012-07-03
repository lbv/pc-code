#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;

#define MAXT 20

#define MAXM 50000
#define MAXN 50000
#define MAXQ 50000
#define MAXW 10000

/*
#define MAXM 100
#define MAXN 100
#define MAXQ 200
#define MAXW 10000
*/


typedef pair<int, int> II;
typedef set<II>        IIS;

void test_case(bool crit = false)
{
    int M = rand() % MAXM + 1;
    int N = rand() % MAXN + 1;
    int Q = rand() % (min(50000, M*N)) + 1;
    if (crit) M = N = Q = 50000;

    printf("\n%d %d %d\n", M, N, Q);

    IIS visit;

    int X = 0;
    int Y = 0;
    while (Q--) {
        int u, v, w;

        do {
            u = rand() % M + 1;
            v = rand() % N + 1;
        } while (visit.count(II(u, v)) > 0);
//        if (crit) u = X++ == 0 ? 50000 : X, v = Y++ == 0 ? 50000 : Y;
        if (crit) u = v = 50000;
        visit.insert(II(u, v));

        w = rand() % MAXW + 1;
        if (crit) w = 10;
        printf("%d %d %d\n", u, v, w);
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

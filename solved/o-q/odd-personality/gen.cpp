#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;


#if 0
#define MAXT 30
#define MAXN 10000
#define MAXM 20000
#endif

#if 1
#define MAXT 20
#define MAXN 10
#define MAXM 20
#endif


typedef pair<int, int> II;


void test_case(bool crit = false)
{
    int n = crit ? MAXN : rand() % (MAXN - 2) + 3;

    int MaxM = min(n * (n-1) / 2, MAXM);
    int m = crit ? MAXM : rand() % (MaxM + 1);

    printf("\n%d %d\n", n, m);

    set<II> s;
    while (m--) {
        int u, v;

        do {
            u = rand() % n;
            v = rand() % n;
        } while (u == v || s.find(II(u, v)) != s.end());

        s.insert(II(u, v));
        s.insert(II(v, u));

        printf("%d %d\n", u, v);
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

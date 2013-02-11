#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;


#if 1
#define MAXT 10
#define MAXN 100000
#define MAXK 100000
#define MAXQ 50000
#define NL   0
#endif

#if 0
#define MAXT 20
#define MAXN 1000
#define MAXK 1000
#define MAXQ 900
#define NL   1
#endif


typedef pair<int, int> II;


void test_case(bool crit = false)
{
    int N = crit ? MAXN : rand() % MAXN + 1;
    int M = rand() % N;

#if NL
    puts("");
#endif

    printf("%d %d\n", N, M);

    set<II> s;
    while (M--) {
        int u, v;
        do {
            u = rand() % N + 1;
            v = rand() % N + 1;
        } while (u == v || s.find(II(u, v)) != s.end());

        s.insert(II(u, v));
        s.insert(II(v, u));
        printf("%d %d\n", u, v);
    }

    int q = crit ? MAXQ : rand() % MAXQ + 1;
    printf("%d\n", q);

    while (q--) {
        int K = rand() % N + 1;

        if (rand() % 10 == 0) K = rand() % MAXK + 1;
        printf("%d\n", K);
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

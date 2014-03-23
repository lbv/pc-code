#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
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
#define MAXN 15
#define MAXK 15
#define MAXQ 20
#define NL   1
#endif

#define Zero(v) memset((v), 0, sizeof(v))


int nodes[MAXN];


void test_case(bool crit = false)
{
    int N = crit ? MAXN : rand() % MAXN + 1;
    int M = crit ? N - 1 : rand() % N;

#if NL
    puts("");
#endif

    printf("%d %d\n", N, M);

    int n = 0;
    for (int i = 2; i <= N; ++i) nodes[n++] = i;
    random_shuffle(nodes, nodes + n);

    for (int i = 0; i < M; ++i) {
        int u = nodes[i];
        int v = rand() % (u - 1) + 1;

        if (rand() % 2 == 0) swap(u, v);

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

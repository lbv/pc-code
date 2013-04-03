#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 0
#define MAXT 200
#define MAXN 100
#define MAXC 100
#endif

#if 1
#define MAXT 20
#define MAXN 12
#define MAXC 100
#endif


int ring[MAXN];
int edges[MAXN][3];

void test_case(bool crit = false)
{
    int n = crit ? MAXN : rand() % (MAXN - 2) + 3;
    printf("\n%d\n", n);

    for (int i = 0; i < n; ++i) ring[i] = i + 1;
    random_shuffle(ring, ring + n);

    for (int i = 0; i < n; ++i) {
        edges[i][0] = ring[i];
        edges[i][1] = ring[(i + 1) % n];
        if (rand() % 2 == 0) swap(edges[i][0], edges[i][1]);
        edges[i][2] = rand() % MAXC + 1;
    }
    random_shuffle(edges, edges + n);

    for (int i = 0; i < n; ++i)
        printf("%d %d %d\n", edges[i][0], edges[i][1], edges[i][2]);
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

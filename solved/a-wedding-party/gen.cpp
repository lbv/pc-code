#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#if 0
#define MAXT 50
#define MAXS 15
#define MAXN 500
#define MAXM 10000
#define MAXW 100
#define EXTRASPACES 0
#endif

#if 1
#define MAXT 20
#define MAXS 5
#define MAXN 5
#define MAXM 8
#define MAXW 100
#define EXTRASPACES 1
#endif


#define Zero(v) memset((v), 0, sizeof(v))


bool edges[MAXN][MAXN];
bool shops[MAXN];


void test_case()
{
    int N = rand() % (MAXN - 1) + 2;

    int TopM = min(MAXM, N * (N-1));
    int M = rand() % TopM + 1;

    int TopS = min(N, MAXS);
    int S = rand() % (TopS + 1);

#if EXTRASPACES
    puts("\n\n");
#endif
    printf("%d %d %d\n", N, M, S);

    Zero(shops);
    for (int i = 0; i < S; ++i) {
        int s;
        do {
            s = rand() % N;
        } while (shops[s]);
        shops[s] = true;
        printf("%s%d", i == 0 ? "" : " ", s);
    }
    putchar('\n');

    Zero(edges);
    while (M--) {
        int u, v, w;
        do {
            u = rand() % N;
            v = rand() % N;
        } while (u == v || edges[u][v]);
        edges[u][v] = true;

        w = rand() % MAXW + 1;
        printf("%d %d %d\n", u, v, w);
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

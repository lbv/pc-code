#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#define MAXT 100
#define MAXN 100
#define MAXK 10000
#define MAXA 500

#define Zero(v) memset(v, 0, sizeof(v))

int vis[MAXA + 1];

void test_case()
{
    int n = rand() % MAXN + 1;
    int K = rand() % MAXK + 1;
    printf("%d %d\n", n, K);

    Zero(vis);
    for (int i = 0; i < n; ++i) {
        int A;

        do {
            A = rand() % MAXA + 1;
        } while(vis[A]);
        vis[A] = true;
        printf("%s%d", i == 0 ? "" : " ", A);
    }
    putchar('\n');
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

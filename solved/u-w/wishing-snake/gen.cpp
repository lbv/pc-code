#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#define MAXT 10
//#define MAXN 100
//#define MAXK 100
//#define MAXCP 1000

#define MAXN 10
#define MAXK 5
#define MAXCP 8

#define Zero(v) memset(v, 0, sizeof(v))

bool rel[MAXCP][MAXCP];

void test_case()
{
    Zero(rel);

    int n = rand() % MAXN + 1;
    printf("%d\n", n);

    for (int i = 0; i < n; ++i) {
        int k = rand() % (MAXK + 1);
        printf("%d\n", k);

        for (int j = 0; j < k; ++j) {
            int u, v;
            do {
                u = rand() % MAXCP;
                v = rand() % MAXCP;
            } while (u == v || rel[u][v]);

            rel[u][v] = true;
            printf("%d %d\n", u, v);
        }
    }
}

int main()
{
    srand(time(NULL));
    
    int T = MAXT;
    printf("%d\n", T);

    while (T--)
        test_case();

    return 0;
}

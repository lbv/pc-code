#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 0
#define MAXT 10
#define MAXN 100
#define MAXS 200
#endif

#if 1
#define MAXT 10
#define MAXN 5
#define MAXS 6
#endif


int perm[52];


void test_case(bool crit = false)
{
    int n = crit ? MAXN : rand() % MAXN + 1;
    printf("\n%d\n", n);

    for (int i = 0; i < 52; ++i) perm[i] = i + 1;
    for (int i = 0; i < n; ++i) {
        random_shuffle(perm, perm + 52);
        for (int j = 0; j < 52; ++j) {
            if (j == 26) putchar('\n');
            else if (j > 0) putchar(' ');
            printf("%d", perm[j]);
        }
        putchar('\n');
    }

    int shuffles = crit ? MAXS : rand() % MAXS + 1;
    while (shuffles--) {
        int k = rand() % n + 1;
        printf("%d\n", k);
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

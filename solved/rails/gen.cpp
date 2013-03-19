#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 0
#define MAXT 25
#define MAXN 1000
#define NL   0
#endif

#if 1
#define MAXT 20
#define MAXN 20
#define NL   1
#endif


int perm[MAXN];


void test_case(bool crit = false)
{
#if NL
    puts("");
#endif

    int N = crit ? MAXN : rand() % MAXN + 1;
    printf("%d\n", N);

    int trains = rand() % N + 1;
    while (trains--) {
        for (int i = 0; i < N; ++i) perm[i] = i + 1;
        random_shuffle(perm, perm + N);

        for (int i = 0; i < N; ++i) {
            if (i > 0) putchar(' ');
            printf("%d", perm[i]);
        }
        puts("");
    }
    puts("0");
}

int main()
{
    srand(time(NULL));

    int T = MAXT;

    test_case(true); --T;
    while (T--) test_case();
    puts("0");

    return 0;
}

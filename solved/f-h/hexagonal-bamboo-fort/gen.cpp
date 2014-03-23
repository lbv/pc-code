#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#define MAXT 25
#define MAXN 100
#define MAXX 100000

#define Zero(v) memset((v), 0, sizeof(v))


bool used[MAXX + 1];


void test_case()
{
    int N = rand() % (MAXN - 5) + 6;

    printf("%d\n", N);
    Zero(used);

    for (int i = 0; i < N; ++i) {
        int x;
        do {
            x = rand() % MAXX + 1;
        } while (used[x]);

        used[x] = true;
        printf("%s%d", i == 0 ? "" : " ", x);
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

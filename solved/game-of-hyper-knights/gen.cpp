#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 200
#define MAXN 1000
#define MAXX 499
#define MAXY 499
#endif

#if 1
#define MAXT 20
#define MAXN 12
#define MAXX 20
#define MAXY 20
#define NL   1
#endif


void test_case(bool crit = false)
{
#if NL
    puts("");
#endif

    int n = crit ? MAXN : rand() % MAXN + 1;
    printf("%d\n", n);

    while (n--) {
        int x = rand() % (MAXX + 1);
        int y = rand() % (MAXY + 1);
        printf("%d %d\n", x, y);
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

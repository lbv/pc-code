#include <cstdio>
#include <cstdlib>
#include <ctime>

#if 0
#define MAXT 10000
#define MAXM 500
#endif

#if 1
#define MAXT 20
#define MAXM 500
#endif


void test_case()
{
    int R = rand() % (MAXM + 1);
    int B = rand() % (MAXM + 1);

    if ((R + B) % 2 == 0) {
        if (rand() % 2 == 0)
            ++R;
        else
            ++B;
    }

    printf("%d %d\n", R, B);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

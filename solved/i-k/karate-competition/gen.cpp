#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 70
#define MAXN 50
#define MAXSKILL 1000

void test_case()
{
    int N = rand() % MAXN + 1;

    printf("%d\n", N);

    for (int i = 0; i < N; ++i)
        printf("%s%d", i == 0 ? "" : " ", rand() % MAXSKILL + 1);
    putchar('\n');
    for (int i = 0; i < N; ++i)
        printf("%s%d", i == 0 ? "" : " ", rand() % MAXSKILL + 1);
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

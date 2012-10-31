#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXCASE 500
#define MAXS 100
#define MAXT 1000
#endif

#if 1
#define MAXCASE 20
#define MAXS 20
#define MAXT 1000
#endif


void test_case()
{
    int s = rand() % MAXS + 1;
    int t = rand() % MAXT + 1;
    printf("%d %d\n", s, t);
}

int main()
{
    srand(time(NULL));

    int T = MAXCASE;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

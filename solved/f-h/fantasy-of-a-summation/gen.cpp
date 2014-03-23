#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 100


void test_case()
{
    
}

int main()
{
    srand(time(NULL));

    puts("1000");
    for (int i = 1; i <= 10; ++i)
        for (int j = 1; j <= 10; ++j)
            for (int k = 1; k <= 10; ++k) {
                printf("%d %d %d\n", i, j, k);
                for (int p = 0; p < i; ++p)
                    printf("%s%d", p == 0 ? "" : " ", rand() % 30 + 1);
                puts("");
            }
    /*
    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();
    */

    return 0;
}

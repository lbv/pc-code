#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 30


void test_case()
{
    int C = rand() % 16;
    int D = rand() % 16;
    int H = rand() % 16;
    int S = rand() % 16;

    printf("%d %d %d %d\n", C, D, H, S);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

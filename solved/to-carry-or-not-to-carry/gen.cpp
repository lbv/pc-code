#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 100


typedef unsigned int u32;


void test_case()
{
    u32 a = rand();
    u32 b = rand();
    printf("%u %u\n", a, b);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;

    while (T--) test_case();

    return 0;
}

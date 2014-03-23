#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 1000


const int mdays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


void test_case()
{
    int m = rand() % 12 + 1;
    int d = rand() % mdays[m - 1] + 1;
    int y = rand() % 100 + 2000;
    printf("%02d%02d%04d\n", m, d, y);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

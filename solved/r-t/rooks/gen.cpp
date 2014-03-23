#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 350
#define MAXN 30


const int limits[31] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
    13,
    14,
    15,
    16,
    11,  // 17
    10,  // 18
    9,   // 19
    9,   // 20
    8,   // 21
    8,   // 22
    8,   // 23
    7,   // 24
    7,   // 25
    7,   // 26
    7,   // 27
    7,   // 28
    7,   // 29
    6    // 30
};


void gen1()
{
    int n = rand() % (MAXN - 1) + 2;

    int lo = n + 1, hi = n*n;
    int k = rand() % (hi - lo + 1) + lo;

    printf("%d %d\n", n, k);
}

void gen2()
{
    int n = rand() % MAXN + 1;
    int k = rand() % (limits[n] + 1);
    printf("%d %d\n", n, k);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) {
        int n = rand() % 10;
        if (n < 2) gen1();
        else gen2();
    }

    return 0;
}

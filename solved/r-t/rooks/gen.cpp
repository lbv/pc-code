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
    17,  // 17
    11,  // 18
    10,  // 19
    9,   // 20
    9,   // 21
    9,   // 22
    8,   // 23
    8,   // 24
    8,   // 25
    8,   // 26
    7,   // 27
    7,   // 28
    7,   // 29
    7    // 30
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

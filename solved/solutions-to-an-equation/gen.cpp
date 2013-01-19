#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT  10000
#define MINI -100000000
#define MAXI  100000000
#define MINA -1000
#define MAXA  1000
#define MAXR  6
#endif

#if 1
#define MAXT  100
#define MINI -100000000
#define MAXI  100000000
#define MINA -1000
#define MAXA  1000
#define MAXR  6
#endif


const int IRange = MAXI - MINI + 1;
const int ARange = MAXA - MINA + 1;


typedef long long i64;


bool valid(i64 n)
{
    return n >= MINI && n <= MAXI;
}

void test_case()
{
    int A = rand() % ARange + MINA;
    int B = rand() % ARange + MINA;

    i64 x0, y0, x1, y1, x2, y2;
    i64 C;
    do {
        x0 = rand() % IRange + MINI;
        y0 = rand() % IRange + MINI;
        C = -1LL * (x0*A + y0*B);
    } while (! valid(x0 - MAXR) || ! valid(x0 + MAXR) ||
             ! valid(y0 - MAXR) || ! valid(y0 + MAXR) ||
             ! valid(C));

    x1 = x0 - (rand() % MAXR + 1);
    x2 = x0 + (rand() % MAXR + 1);
    y1 = y0 - (rand() % MAXR + 1);
    y2 = y0 + (rand() % MAXR + 1);

    printf("%d %d %lld %lld %lld %lld %lld\n", A, B, C, x1, x2, y1, y2);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

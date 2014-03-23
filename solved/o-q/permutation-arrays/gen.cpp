#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 0
#define MAXT 8
#define MAXN 10000
#define MINF -1000000
#define MAXF 1000000
#endif

#if 1
#define MAXT 20
#define MAXN 25
#define MINF -1000000
#define MAXF 1000000
#endif



const int RangeF = MAXF - MINF + 1;

const char fmt[6][16] = {
    "",
    "%d.%01d",
    "%d.%02d",
    "%d.%03d",
    "%d.%04d",
    "%d.%05d",
};

const int p10[] = {
    1,
    10,
    100,
    1000,
    10000,
    100000
};

int perm[MAXN];


void print_float()
{
    int dig = rand() % 6;

    if (dig == 0)
        printf("%d", rand() % RangeF + MINF);
    else
        printf(fmt[dig], rand() % RangeF + MINF, rand() % p10[dig]);
}

void test_case()
{
    int n = rand() % MAXN + 1;
    for (int i = 0; i < n; ++i)
        perm[i] = i + 1;
    random_shuffle(perm, perm + n);

    for (int i = 0; i < n; ++i)
        printf("%c%d", i == 0 ? '\n' : ' ', perm[i]);
    puts("");

    for (int i = 0; i < n; ++i) {
        if (i > 0) putchar(' ');
        print_float();
    }
    puts("");
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

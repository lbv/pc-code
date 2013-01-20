#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#define MAXT 50
#define MAXN 20

const int MaxMult = MAXN / 4;

int ns[MAXN];

void test_case(bool crit = false)
{
    int mult = crit ? MaxMult : rand() % MaxMult + 1;
    int N = 4 * mult;

    printf("%d\n", N);
    for (int i = 0; i < N; ++i) ns[i] = i + 1;

    random_shuffle(ns, ns + N);

    for (int i = 0; i < N; ++i) {
        if (i > 0) putchar(' ');
        printf("%d", ns[i]);
    }
    putchar('\n');
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    test_case(true); --T;
    while (T--) test_case();

    return 0;
}

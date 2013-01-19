#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 0
#define MAXT     10000
#define EXTRA_NL 0
#endif

#if 1
#define MAXT     20
#define EXTRA_NL 1
#endif


const int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
const int nprimes  = 12;

int used[12];

void test_case()
{
    int n = rand() % nprimes + 1;
#if EXTRA_NL
    puts("");
#endif
    printf("%d\n", n);

    for (int i = 0; i < 12; ++i) used[i] = i;
    random_shuffle(used, used + 12);

    for (int i = 0; i < n; ++i) {
        int p = primes[used[i]];
        int r = rand() % (p - 1) + 1;
        printf("%d %d\n", p, r);
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

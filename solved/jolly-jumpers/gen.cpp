#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 0
#define MAXT 100
#define MAXN 3000
#endif

#if 1
#define MAXT 20
#define MAXN 10
#endif


void gen1(bool crit = false)
{
    int n = crit ? MAXN : rand() % (MAXN + 1);
    printf("%d", n);

    int lo = -2 * n;
    int hi = 2 * n;
    int range = hi - lo + 1;
    while (n--) {
        int x = rand() % range + lo;
        printf(" %d", x);
    }
    putchar('\n');
}

int seq[MAXN];

void gen2(bool crit = false)
{
    int n = crit ? MAXN : rand() % (MAXN + 1);
    printf("%d", n);
    if (n == 0) { puts(""); return; }

    for (int i = 0; i < n - 1; ++i) seq[i] = i + 1;
    random_shuffle(seq, seq + n - 1);

    int last = rand() % (n + 1);
    printf(" %d", last);

    for (int i = 1; i < n; ++i) {
        int dir = rand() % 2;
        last = last + seq[i - 1] * (dir == 0 ? 1 : -1);
        printf(" %d", last);
    }

    putchar('\n');
}

int main()
{
    srand(time(NULL));

    int T = MAXT;

    gen1(true); --T;
    gen2(true); --T;
    while (T--) {
        int n = rand() % 10;
        if (n < 3) gen1();
        else gen2();
    }

    return 0;
}

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;


#if 0
#define MAXT 100
#define MAXN 100
#define MAXD 1000000000
#endif

#if 1
#define MAXT 20
#define MAXN 10
#define MAXD 10000
#endif


int ds[MAXN];


void test_case(bool crit = false)
{
    int D = crit ? MAXD : rand() % MAXD + 1;
    if (!crit && rand() % 10 == 0) D = rand() % 1000;

    int N = crit ? MAXN : rand() % min(D, MAXN + 1);

    printf("%d %d\n", N, D);

    set<int> s;
    for (int i = 0; i < N; ++i) {
        int d;
        do {
            d = rand() % (D - 1) + 1;
        } while (s.find(d) != s.end());
        s.insert(d);
        ds[i] = d;
    }
    sort(ds, ds + N);

    for (int i = 0; i < N; ++i) {
        if (i > 0) putchar(' ');
        char rock = rand() % 2 == 0 ? 'B' : 'S';
        printf("%c-%d", rock, ds[i]);
    }
    puts("");
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

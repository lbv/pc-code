#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;


#if 0
#define MAXT 5
#define MAXN 100000
#define MAXQ 50000
#define MAXI 100000000
#define NL   0
#endif

#if 1
#define MAXT 20
#define MAXN 30
#define MAXQ 15
#define MAXI 40
#define NL   1
#endif


int pts[MAXN];


void test_case(bool crit = false)
{
#if NL
    puts("");
#endif

    int n = crit ? MAXN : rand() % MAXN + 1;
    int q = crit ? MAXQ : rand() % MAXQ + 1;
    printf("%d %d\n", n, q);

    set<int> s;
    for (int i = 0; i < n; ++i) {
        int p;
        do {
            p = rand() % (MAXI + 1);
        } while (s.find(p) != s.end());
        s.insert(p);
        pts[i] = p;
    }
    sort(pts, pts + n);
    for (int i = 0; i < n; ++i) {
        if (i > 0) putchar(' ');
        printf("%d", pts[i]);
    }
    putchar('\n');

    while (q--) {
        int a = rand() % (MAXI + 1);
        int b = rand() % (MAXI + 1);

        if (a > b) swap(a, b);
        printf("%d %d\n", a, b);
    }
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

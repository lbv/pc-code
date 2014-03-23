#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;


#if 1
#define MAXT 100
#define MAXN 100
#define MAXL 100
#define MINL 5
#define NL   0
#endif

#if 0
#define MAXT 20
#define MAXN 50
#define MAXL 100
#define MINL 5
#define NL   1
#endif


const int RangeL = MAXL - MINL + 1;

typedef pair<int, int> II;
typedef pair<II, II>   IIII;


void rand_pair(int &x, int &y, int L, int W)
{
    if (rand() % 2 == 0) {
        x = rand() % 2 == 0 ? 0 : L;
        y = rand() % (W + 1);
    }
    else {
        x = rand() % (L + 1);
        y = rand() % 2 == 0 ? 0 : W;
    }
}

void test_case(bool crit = false)
{
#if NL
    puts("");
#endif

    int L = crit ? MAXL : rand() % RangeL + MINL;
    int W = crit ? MAXL : rand() % RangeL + MINL;

    int MaxN =
        2*(L - 1) * (2 * (W - 1) + L - 1) +
        2*(W - 1) * (2 * (L - 1) + W - 1);
    MaxN /= 2;

    if (MaxN > MAXN) MaxN = MAXN;

    int n = crit ? MaxN : rand() % (MaxN + 1);
    printf("%d %d %d\n", n, L, W);

    set<IIII> s;
    while (n--) {
        int x1, y1, x2, y2;
        do {
            rand_pair(x1, y1, L, W);
            rand_pair(x2, y2, L, W);
        } while (x1 == x2 || y1 == y2 ||
                 s.find(IIII(II(x1, y1), II(x2, y2))) != s.end());

        s.insert(IIII(II(x1, y1), II(x2, y2)));
        s.insert(IIII(II(x2, y2), II(x1, y1)));
        printf("%d %d %d %d\n", x1, y1, x2, y2);
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

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 0
#define MAXT 100
#define MAXP 10000
#define MAXN 100
#define MAXB 10000
#define NL   0
#endif

#if 1
#define MAXT 20
#define MAXP 100
#define MAXN 10
#define MAXB 100
#define NL   1
#endif


int bills[MAXN];


void test_case(bool crit = false)
{
#if NL
    puts("");
#endif
    int price = crit ? MAXP : rand() % MAXP + 1;
    int n     = crit ? MAXN : rand() % (MAXN - 1) + 2;

    printf("%d\n%d\n", price, n);

    int sum = 0;
    for (int i = 0; i < n; ++i) {
        int bill;

        do {
            bill = rand() % MAXB + 1;
        } while (i == n - 1 && sum + bill < price);

        sum += bill;
        bills[i] = bill;
    }
    random_shuffle(bills, bills + n);
    for (int i = 0; i < n; ++i)
        printf("%d\n", bills[i]);
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

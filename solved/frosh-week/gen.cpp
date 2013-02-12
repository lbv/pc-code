#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 1
#define MAXT 20
#define MAXN 1000000
#define NL   0
#endif

#if 0
#define MAXT 20
#define MAXN 100
#define NL   1
#endif


int nums[MAXN];


void test_case(bool crit = false)
{
#if NL
    puts("");
#endif

    int n = crit ? MAXN : rand() % MAXN + 1;
    printf("%d\n", n);

    for (int i = 0; i < n; ++i)
        nums[i] = i + 1;

    random_shuffle(nums, nums + n);

    for (int i = 0; i < n; ++i)
        printf("%d\n", nums[i]);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;

    test_case(true); --T;
    while (T--) test_case();

    return 0;
}

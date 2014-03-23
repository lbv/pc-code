#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;


#define MAXT 100
#define MAXK 1000000000
#define MAXA 10000000


void test_case()
{
    int n = rand() % 18 + 1;
    int K = rand() % MAXK + 1;

    set<int> used;
    printf("%d %d\n", n, K);

    for (int i = 0; i < n; ++i) {
        if (i != 0) putchar(' ');

        int A;
        do {
            A = rand() % MAXA + 1;
        } while (used.find(A) != used.end());

        used.insert(A);

        printf("%d", A);
    }
    putchar('\n');
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

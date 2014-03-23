#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#define MAXT 100

/*
#define MAXN 30
#define MAXP 30
#define MAXQ 30
#define MAXW 10
*/

#define MAXN 10
#define MAXP 30
#define MAXQ 30
#define MAXW 10



int eggs[MAXN];


void test_case()
{
    int N = rand() % MAXN + 1;
    int P = rand() % MAXP + 1;
    int Q = rand() % MAXQ + 1;

    printf("%d %d %d\n", N, P, Q);

    for (int i = 0; i < N; ++i)
        eggs[i] = rand() % MAXW + 1;

    sort(eggs, eggs + N);
    printf("%d", eggs[0]);

    for (int i = 1; i < N; ++i)
        printf(" %d", eggs[i]);
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

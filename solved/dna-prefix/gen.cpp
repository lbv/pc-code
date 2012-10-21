#include <cstdio>
#include <cstdlib>
#include <ctime>


/*
#define MAXT 10
#define MAXN 50000
#define MAXLEN 50
*/


#define MAXT 25
#define MAXN 10
#define MAXLEN 3



const char dna[] = "ACGT";


void test_case()
{
    int N = rand() % MAXN + 1;
    printf("%d\n", N);

    while (N--) {
        int len = rand() % MAXLEN + 1;

        for (int i = 0; i < len; ++i)
            putchar(dna[rand() % 4]);
        putchar('\n');
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

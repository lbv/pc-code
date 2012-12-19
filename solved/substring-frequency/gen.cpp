#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 5
#define MAXLEN 1000000
#endif

#if 0
#define MAXT 10
#define MAXLEN 20
#endif


char A[MAXLEN + 1];
char B[MAXLEN + 1];


void test_case(bool crit = false)
{
    int lena = crit ? MAXLEN : rand() % MAXLEN + 1;

    for (int i = 0; i < lena; ++i)
        A[i] = 'a' + rand() % 26;
    A[lena] = 0;

    if (rand() % 5 == 0) {
        int lenb = rand() % lena + 1;
        for (int i = 0; i < lenb; ++i)
            B[i] = 'a' + rand() % 26;
        B[lenb] = 0;
    }
    else {
        int to = rand() % lena;
        int from = rand() % (to + 1);
        int i = 0;
        while (from <= to)
            B[i++] = A[from++];
        B[i] = 0;
    }

    printf("%s\n%s\n", A, B);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    for (int i = 0; i < MAXLEN; ++i) putchar('p');
    putchar('\n');
    for (int i = 1; i < MAXLEN; ++i) putchar('p');
    puts("q"); --T;

    for (int i = 0; i < MAXLEN; ++i) putchar('p');
    putchar('\n');
    for (int i = 1, I = MAXLEN/2; i < I; ++i) putchar('p');
    puts(""); --T;

    test_case(true); --T;
    while (T--) test_case();

    return 0;
}

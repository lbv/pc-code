#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 300

#define MAXLEN 30

void test_case()
{
    int len = rand() % MAXLEN + 1;

    int d = rand() % 9 + 1;
    printf("%d", d);
    --len;

    while (len--) {
        d = rand() % 10;
        printf("%d", d);
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

#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 200
#define MAXLEN 50

void test_case()
{
    int len = rand() % MAXLEN + 1;

    for (int i = 0; i < len; ++i) {
        char c = rand() % 26 + 'A';
        if (rand() % 4 == 0)
            c = '?';
        putchar(c);
    }
    puts("");
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

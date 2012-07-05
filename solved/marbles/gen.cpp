#include <cstdio>
#include <cstdlib>
#include <ctime>

//#define MAXT 10000
#define MAXM 500

#define MAXT 1000

void test_case()
{
    int R = rand() % MAXM;
    int B = rand() % MAXM;

    if ((R + B) % 2 == 0) {
        if (rand() % 2 == 0)
            ++R;
        else
            ++B;
    }

    printf("%d %d\n", R, B);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

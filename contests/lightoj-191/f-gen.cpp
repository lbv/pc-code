#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 100

#define MAXC 200

void test_case()
{
    puts("");

    int x, y, X, Y;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (j == 0) {
                x = rand() % (MAXC - 20);
                y = rand() % (MAXC - 20);
                x -= 95;
                y -= 95;
                X = x, Y = y;
            }
            else {
                x = rand() % 7;
                y = rand() % 7;
                x += X;
                y += Y;
            }

            printf("%s%d %d", j == 0 ? "" : " ", x, y);
        }
        puts("");
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

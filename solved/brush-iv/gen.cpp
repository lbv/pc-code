#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

#define MAXT 1000
#define MAXN 16
#define MAXCOORD 1000

#define Zero(v) memset(v, 0, sizeof(v))

bool map[MAXCOORD + 1][MAXCOORD + 1];

void test_case()
{
    int N = rand() % MAXN + 1;

    printf("\n%d\n", N);

    Zero(map);

    while (N--) {
        int x, y;
        do {
            x = rand() % MAXCOORD + 1;
            y = rand() % MAXCOORD + 1;
        } while (map[x][y]);
        map[x][y] = true;

        printf("%d %d\n", x, y);
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

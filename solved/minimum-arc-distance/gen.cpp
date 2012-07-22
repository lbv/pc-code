#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 100

void test_case()
{
    int ox = rand() % 1000 + 4500;
    int oy = rand() % 1000 + 4500;

    int dx = rand() % 4000;
    int dy = rand() % 4000;

    int bx = rand() % 2 == 0 ? ox + dx : ox - dx;
    int by = rand() % 2 == 0 ? oy + dy : oy - dy;

    int cx = rand() % 2 == 0 ? ox + dx : ox - dx;
    int cy = rand() % 2 == 0 ? oy + dy : oy - dy;

    printf("%d %d %d %d %d %d\n", ox, oy, bx, by, cx, cy);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

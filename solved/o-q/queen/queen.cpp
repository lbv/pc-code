#include <cstdio>
#include <cstdlib>


int x1, x2, y1, y2;


int solve()
{
    if (x1 == x2 && y1 == y2) return 0;
    if (x1 == x2 || y1 == y2) return 1;
    if (abs(x1 - x2) == abs(y1 - y2)) return 1;
    return 2;
}

int main()
{
    while (true) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (x1 == 0) break;

        printf("%d\n", solve());
    }

    return 0;
}

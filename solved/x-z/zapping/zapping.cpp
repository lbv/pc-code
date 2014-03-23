#include <algorithm>
#include <cstdio>
using namespace std;

int a, b;

int solve()
{
    int d1 = a - b;
    int d2 = b - a;

    if (d1 < 0) d1 += 100;
    if (d2 < 0) d2 += 100;

    return min(d1, d2);
}

int main()
{
    while (true) {
        scanf("%d%d", &a, &b);
        if (a < 0) break;

        printf("%d\n", solve());
    }

    return 0;
}

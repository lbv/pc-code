#include <cstdio>


int x, y, z;


int solve()
{
    return z * (2*x - y) / (x + y);
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d%d", &x, &y, &z);
        printf("%d\n", solve());
    }

    return 0;
}

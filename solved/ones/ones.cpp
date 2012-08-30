#include <cstdio>

int n;

int solve()
{
    int cnt = 1;
    int m = 1 % n;

    while (m != 0) {
        m = m*10 + 1;
        m %= n;
        ++cnt;
    }

    return cnt;
}

int main()
{
    while (true) {
        if (scanf("%d", &n) != 1) break;

        printf("%d\n", solve());
    }

    return 0;
}

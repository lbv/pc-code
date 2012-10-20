#include <cstdio>


int n;


int josephus(int n, int k)
{
    if (n == 1) return 0;
    return (josephus(n-1, k) + k) % n;
}

int solve()
{
    for (int m = 2; ; ++m)
        if (josephus(n - 1, m) == 0)
            return m;
    return -1;
}

int main()
{
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        printf("%d\n", solve());
    }

    return 0;
}

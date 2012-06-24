#include <cstdio>

int N;

int josephus(int n, int k)
{
    if (n == 1) return 0;
    return (josephus(n-1, k) + k) % n;
}

int solve()
{
    for (int m = 1; ; ++m)
        if (josephus(N - 1, m) == 11)
            return m;
    return -1;
}

int main()
{
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;

        printf("%d\n", solve());
    }

    return 0;
}

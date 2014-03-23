#include <cstdio>

#define LIM 100

int N;
int memo[LIM + 1];

int f(int n)
{
    if (n > LIM) return n - 10;
    if (memo[n] != 0) return memo[n];
    return memo[n] = f(f(n + 11));
}

int main()
{
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;

        printf("f91(%d) = %d\n", N, f(N));
    }

    return 0;
}

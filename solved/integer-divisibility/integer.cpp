#include <cstdio>

int solve(int n, int d)
{
    int mod = d % n;
    int ans = 1;

    while (mod != 0) {
        mod = mod*10 + d;
        if (mod >= n) mod %= n;
        ++ans;
    }

    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int n, d;
        scanf("%d%d", &n, &d);

        printf("Case %d: %d\n", ++ncase, solve(n, d));
    }

    return 0;
}

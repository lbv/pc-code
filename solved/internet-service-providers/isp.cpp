#include <cmath>
#include <cstdio>

typedef long long i64;

int N, C;

i64 f(i64 T)
{
    return T*C*N - T*T*N*N;
}

int solve()
{
    if (N == 0) return 0;
    double T = 1.0 * C / (2.0*N);
    i64 ans = ceil(T);
    i64 profit = f(ans);

    while (f(ans - 1) >= profit) --ans;

    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &N, &C);

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}

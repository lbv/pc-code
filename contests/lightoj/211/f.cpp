#include <cstdio>

int M, N, L;

bool solve()
{
    int a, b, c;
    for (b = 1; b <= 100; ++b)
        for (c = 1; c <= 10; ++c) {
            a = L - b*b - c*c;

            if (N - b - c*c == a*a && M - b*b - c == a*a) return true;
        }
    return false;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d", &M, &N, &L);

        printf("Case %d: %s\n", ++ncase, solve() ? "Yes" : "No");
    }

    return 0;
}

#include <cstdio>

int cmod(int x, int m) { return x < m ? x : x%m; }

int modPow(int b, int e, int m) {
    int res = 1;
    for (; e; e >>= 1, b = cmod(b*b, m)) if (e & 1) res = cmod(res*b, m);
    return res;
}

int calc(int sum, int n, int k, int m)
{
    int tmp = modPow(n, k-1, m);
    return cmod(cmod(tmp * cmod(k, m), m) * sum, m);
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        int n, K, MOD;
        scanf("%d%d%d", &n, &K, &MOD);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int a; scanf("%d", &a);
            sum = cmod(sum + cmod(a, MOD), MOD);
        }
        printf("Case %d: %d\n", ncase++, calc(sum, n, K, MOD));
    }

    return 0;
}

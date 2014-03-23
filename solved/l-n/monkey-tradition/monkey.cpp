#include <cstdio>


#define MAXN 12


typedef long long i64;


int n;
i64 ps[MAXN];
i64 rs[MAXN];

template<typename T>
void ext_euclid(T a, T b, T &x, T &y, T &g) {
    x = 0; y = 1; g = b;
    T m, n, q, r;
    for (T u=1, v=0; a != 0; g=a, a=r) {
        q = g / a; r = g % a;
        m = x-u*q; n = y-v*q;
        x=u; y=v; u=m; v=n;
    }
}

template <typename T>
T chinese_rem(int k, T *ns, T *as)
{
    T N = 1, x = 0, r, s, g;
    for (int i = 0; i < k; ++i) N *= ns[i];
    for (int i = 0; i < k; ++i) {
        ext_euclid(ns[i], N/ns[i], r, s, g);
        x += as[i]*s*(N/ns[i]);
        x %= N;
    }
    if (x < 0) x += N;
    return x;
}

i64 solve()
{
    return chinese_rem(n, ps, rs);
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            scanf("%lld%lld", &ps[i], &rs[i]);

        printf("Case %d: %lld\n", ++ncase, solve());
    }

    return 0;
}

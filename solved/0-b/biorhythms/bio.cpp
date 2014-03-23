#include <cstdio>


const int rhythms[] = { 23, 28, 33 };
const int lcm       = 23 * 28 * 33;

int days[3];
int today;


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
T chinese_rem(int k, const T *ns, const T *as)
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

int solve()
{
    for (int i = 0; i < 3; ++i) days[i] %= rhythms[i];
    int next = chinese_rem(3, rhythms, days);
    if (next <= today) next += lcm;
    return next - today;
}

int main()
{
    int ncase = 0;
    while (true) {
        scanf("%d%d%d%d", &days[0], &days[1], &days[2], &today);
        if (today < 0) break;

        printf("Case %d: the next triple peak occurs in %d days.\n",
               ++ncase, solve());
    }

    return 0;
}

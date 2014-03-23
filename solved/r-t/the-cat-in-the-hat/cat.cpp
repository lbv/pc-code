#include <cmath>
#include <cstdio>

#define EPS (1e-9)

typedef long long i64;

i64 H;  // height of first cat
i64 Q;  // number of worker cats

i64 N;  // number of cats in each non-worker hat
i64 m;  // height of the tree of cats (number of levels)

i64 X;  // number of non-worker cats
i64 Y;  // sum of all heights

i64 ipow(i64 b, i64 e) {
    i64 res = 1; for (; e; e >>= 1, b *= b) if (e & 1) res *= b;
    return res;
}

// returns sum{i=0 to k}{ x^k }
i64 sum(i64 x, i64 k)
{
    if (x == 1) return k + 1;
    return (ipow(x, k + 1) - 1) / (x - 1);
}

void find_n_m()
{
    if (Q == 1) {
        N = 1;
        m = ceil(log2(H)) + 1;
        return;
    }

    double x = log(H) / log(Q);

    i64 lo = 1;
    i64 hi = 1 << 16;
    while (true) {
        N = (lo + hi) / 2;

//        printf("  lo(%lld) hi(%lld) N(%lld)\n", lo, hi, N);

        double y = log(N+1)/log(N);
        if (fabs(y-x) < EPS) break;

        if (y > x) lo = N + 1;
        else hi = N - 1;
    }

    i64 p = 1;
    m = 0;

    while (p != Q)
        ++m, p *= N;
    ++m;
}

void solve()
{
    find_n_m();
//    printf("  ~~ N(%lld) m(%lld)\n", N, m);

    X = sum(N, m - 2);

    Y = 0;
    i64 f1 = 1;
    i64 f2 = Q;
    for (int i = 1; i <= m; ++i) {
        Y += f1 * f2;
        f1 *= N + 1;
        f2 /= N;
    }
}


int main()
{
    while (true) {
        scanf("%lld%lld", &H, &Q);
        if (H == 0 && Q == 0) break;

        solve();

        printf("%lld %lld\n", X, Y);
    }

    return 0;
}

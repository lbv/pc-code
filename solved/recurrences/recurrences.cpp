#include <cstdio>
#include <cstring>

#define MAXD 15

#define Zero(v) memset(v, 0, sizeof(v))

typedef long long i64;

i64 MOD;

// Matrix Exponentiation
typedef i64 t_m;
#define MAXR MAXD
#define MAXC MAXD
struct Matrix {
    int r, c;
    t_m m[MAXR][MAXC];
    void init(int R, int C) { Zero(m); r=R; c=C; }
};

void matrix_mul(const Matrix &a, const Matrix &b, Matrix &c)
{
    c.r = a.r, c.c = b.c;
    t_m x;
    for (int i = 0; i < c.r; ++i)
        for (int j = 0; j < c.c; ++j) {
            x = 0;
            for (int k = 0; k < a.c; ++k)
                x += a.m[i][k] * b.m[k][j];
            c.m[i][j] = x % MOD;
        }
}

void matrix_exp(const Matrix &m, int e, Matrix &r)
{
    if (e == 1) { r = m; return; }

    Matrix x;
    if (e % 2 == 0) {
        matrix_exp(m, e / 2, x);
        matrix_mul(x, x, r);
        return;
    }

    matrix_exp(m, e-1, x);
    matrix_mul(x, m, r);
}

int d, n, m;
int as[MAXD];
int fs[MAXD];

i64 ans;

void solve()
{
    if (n <= d) {
        ans = fs[n - 1];
        return;
    }

    Matrix O;
    O.init(d, d);
    for (int j = 0; j < d; ++j)
        O.m[0][j] = as[j] % m;

    int i = 1, j = 0;
    while (i < d) O.m[i++][j++] = 1;

    MOD = m;

    Matrix R;
    matrix_exp(O, n - d, R);

    ans = 0;
    for (int j = 0, i = d - 1; j < d; ++j, --i)
        ans += R.m[0][j] * fs[i];

    ans %= MOD;
}

int main()
{
    while (true) {
        scanf("%d%d%d", &d, &n, &m);
        if (d == 0) break;

        for (int i = 0; i < d; ++i) scanf("%d", &as[i]);
        for (int i = 0; i < d; ++i) scanf("%d", &fs[i]);

        solve();

        printf("%lld\n", ans);
    }

    return 0;
}

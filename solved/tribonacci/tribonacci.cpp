#include <cstdio>
#include <cstring>

#define MOD 1000000009LL

#define Zero(v) memset(v, 0, sizeof(v))

typedef long long i64;

// Matrix Exponentiation
typedef i64 t_m;
#define MAXR 3
#define MAXC 3
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

void matrix_exp(const Matrix &m, i64 e, Matrix &r)
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

Matrix O, R;
i64 n;

i64 solve()
{
    if (n == 1) return 0;
    if (n == 2) return 1;
    if (n == 3) return 2;

    Matrix M = O;
    matrix_exp(M, n - 3, R);

    i64 ans = R.m[0][0] * 2 + R.m[0][1];
    ans %= MOD;
    return ans;
}

void prepare()
{
    O.init(3, 3);
    O.m[0][0] = 1;
    O.m[0][1] = 1;
    O.m[0][2] = 1;

    O.m[1][0] = 1;
    O.m[1][1] = 0;
    O.m[1][2] = 0;

    O.m[2][0] = 0;
    O.m[2][1] = 1;
    O.m[2][2] = 0;
}

int main()
{
    prepare();

    while (true) {
        scanf("%lld", &n);
        if (n == 0) break;

        printf("%lld\n", solve());
    }

    return 0;
}

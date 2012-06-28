#include <cstdio>
#include <cstring>

#define Zero(v) memset(v, 0, sizeof(v))

typedef long long i64;

int MOD;

// Matrix Exponentiation
typedef i64 t_m;
#define MAXR 2
#define MAXC 2
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

int n, m;

Matrix O;

int solve()
{
    MOD = 1 << m;

    if (n == 0) return 0 % MOD;
    if (n == 1) return 1 % MOD;

    Matrix R;

    matrix_exp(O, n - 1, R);

    return R.m[0][0] % MOD;
}

void prepare()
{
    O.init(2, 2);
    O.m[0][0] = 1;
    O.m[0][1] = 1;
    O.m[1][0] = 1;
    O.m[1][1] = 0;
}

int main()
{
    prepare();

    while (true) {
        if (scanf("%d%d", &n, &m) != 2) break;

        printf("%d\n", solve());
    }

    return 0;
}

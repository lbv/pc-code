#include <cstdio>
#include <cstring>


#define MAXM 4

#define Zero(v) memset((v), 0, sizeof(v))


typedef long long i64;
typedef unsigned long long u64;


i64 Mod;


//
// Matrix Exponentiation
//
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
            c.m[i][j] = x % Mod;
        }
}

void matrix_exp(const Matrix &m, u64 e, Matrix &r)
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


int a, b, n, m;
int p10[MAXM + 1];
Matrix O;


int solve()
{
    Mod = p10[m];
    if (n == 0) return a % Mod;
    if (n == 1) return b % Mod;

    Matrix R;
    matrix_exp(O, n - 1, R);

    i64 res = R.m[0][0] * b + R.m[0][1] * a;
    res %= Mod;

    return res;
}

void prepare()
{
    O.init(2, 2);
    O.m[0][0] = 1;
    O.m[0][1] = 1;
    O.m[1][0] = 1;
    O.m[1][1] = 0;

    p10[0] = 1;
    for (int i = 1; i <= MAXM; ++i)
        p10[i] = p10[i - 1] * 10;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d%d%d", &a, &b, &n, &m);
        printf("%d\n", solve());
    }

    return 0;
}

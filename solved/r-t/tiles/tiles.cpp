#include <cstdio>
#include <cstring>

typedef unsigned long long u64;

#define Zero(v) memset(v, 0, sizeof(v))

#define MOD 10007

// Matrix Exponentiation
typedef u64 t_m;
#define MAXR 4
#define MAXC 4
struct Matrix {
    int r, c;
    t_m m[MAXR][MAXC];
    void init(int R, int C) { Zero(m); r=R; c=C; }
    void print() {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j)
                printf("%4llu  ", m[i][j]);
            printf("\n");
        }
    }
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

Matrix A, O, R;

void prepare()
{
    O.init(4, 4);

    O.m[0][0] = 1;
    O.m[0][1] = 1;
    O.m[0][2] = 1;
    O.m[0][3] = 1;

    O.m[1][0] = 1;

    O.m[2][1] = 1;
    O.m[2][3] = 1;

    O.m[3][1] = 1;
    O.m[3][2] = 1;
}

int solve(int N)
{
    if (N == 1) return 1;
    if (N == 2) return 2;

    A = O;
    matrix_exp(A, N-2, R);

    return (2*R.m[0][0] + R.m[0][1] + R.m[0][2] + R.m[0][3]) % MOD;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int N;
        scanf("%d", &N);

        printf("Case %d: %d\n", ++ncase, solve(N));
    }

    return 0;
}

#include <cstdio>
#include <cstring>

#define Zero(v) memset(v, 0, sizeof(v))

#define MOD 1000000007

typedef long long i64;

// Matrix Exponentiation
typedef i64 t_m;
#define MAXR 2
#define MAXC 2
struct Matrix {
    int r, c;
    t_m m[MAXR][MAXC];
    void init(int R, int C) { Zero(m); r=R; c=C; }
};

bool modflg;

void matrix_mul(const Matrix &a, const Matrix &b, Matrix &c)
{
    c.r = a.r, c.c = b.c;
    t_m x;
    for (int i = 0; i < c.r; ++i)
        for (int j = 0; j < c.c; ++j) {
            x = 0;
            for (int k = 0; k < a.c; ++k)
                x += a.m[i][k] * b.m[k][j];
            if (x >= MOD) modflg = true;
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
i64 N, M, X, Y, K;
i64 sol;


void find_coefficients(i64 step, i64 &c1, i64 &c2)
{
    if (step == 1) {
        c1 = 1;
        c2 = 1;
        return;
    }

    matrix_exp(O, step - 1, R);
    c1 = R.m[0][0] + R.m[1][0];
    c2 = R.m[0][1] + R.m[1][1];
}

bool solve()
{
    /*
     * Let a(i) be the number of a's of the ith string, and b(i) the number
     * of b's. We'll find a(1) and b(1) from the following system of equations:
     *
     *   c1 * a(1) + c2 * b(1) = X
     *   c3 * a(1) + c4 * b(1) = Y
     */
    i64 c1, c2, c3, c4;
    modflg = false;
    find_coefficients(N, c1, c2);
    find_coefficients(M, c3, c4);

    if (modflg) return false;

    i64 det_a = X*c4 - Y*c2;
    i64 det_b = c1*Y - c3*X;
    i64 det_den = c1*c4 - c2*c3;

    if (det_a % det_den != 0 || det_b % det_den != 0) return false;

    i64 a1 = det_a / det_den;
    i64 b1 = det_b / det_den;

    if (a1 < 0 || b1 < 0) return false;

    if (K == 1) {
        sol = (a1 + b1) % MOD;
        return true;
    }

    matrix_exp(O, K-1, R);
    sol = (R.m[0][0] + R.m[1][0]) * a1 + (R.m[0][1] + R.m[1][1]) * b1;
    sol %= MOD;

    return true;
}

void init()
{
    O.init(2, 2);
    O.m[0][0] = 0;
    O.m[0][1] = 1;

    O.m[1][0] = 1;
    O.m[1][1] = 1;
}

int main()
{
    init();

    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%lld%lld%lld%lld%lld", &N, &X, &M, &Y, &K);

        if (solve())
            printf("%lld\n", sol);
        else
            puts("Impossible");
    }

    return 0;
}

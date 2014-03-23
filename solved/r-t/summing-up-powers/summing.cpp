#include <cstdio>
#include <cstring>

typedef unsigned int       u32;
typedef unsigned long long u64;

#define Sc(t,v) static_cast<t>(v)
#define Zero(v) memset(v, 0, sizeof(v))

#define MAXK 50

// Binomial coefficients
#define BCSIZE MAXK
u32 bc[BCSIZE + 1][BCSIZE + 1];
void choose_table() {
    for (int n = 0; n <= BCSIZE; ++n) bc[n][0] = 1;
    for (int n = 1; n <= BCSIZE; ++n) { bc[n][n] = 1; bc[n][1] = n; }
    for (int n = 3; n <= BCSIZE; ++n)
        for (int k = 2; k < n; ++k)
            bc[n][k] = (bc[n-1][k-1] + bc[n-1][k]);
}

typedef u32 t_m;
#define MAXR (MAXK + 2)
#define MAXC (MAXK + 2)
struct Matrix {
    int r, c;
    t_m m[MAXR][MAXC];
    void init(int R, int C) { Zero(m); r=R; c=C; }
    void print() {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j)
                printf("%4d  ", m[i][j]);
            printf("\n");
        }
    }
};

void matrix_mul(const Matrix &a, const Matrix &b, Matrix &c)
{
    c.r = a.r, c.c = b.c;
    int x;
    for (int i = 0; i < c.r; ++i)
        for (int j = 0; j < c.c; ++j) {
            x = 0;
            for (int k = 0; k < a.c; ++k)
                x += a.m[i][k] * b.m[k][j];
            c.m[i][j] = x;
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


u64 N;
int K;
Matrix A, R;

void fill_matrices()
{
    A.init(K+2, K+2);
    for (int i = 0; i <= K; ++i)
        for (int j = 0; j <= i; ++j)
            A.m[i][j] = bc[i][i-j];
    for (int j = 0; j <= K; ++j)
        A.m[K + 1][j] = bc[K][K-j];
    A.m[K+1][K+1] = 1;
}

int main()
{
    choose_table();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%llu%d", &N, &K);

        if (N == 1) {
            printf("Case %d: 1\n", ++ncase);
            continue;
        }

        fill_matrices();
        matrix_exp(A, N-1, R);

        u32 ans = 0;
        for (int i = 0; i <= K + 1; ++i)
            ans += R.m[K+1][i];

        printf("Case %d: %u\n", ++ncase, ans);

    }

    return 0;
}

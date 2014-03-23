#include <cstdio>
#include <cstring>


#define MAXN 30

#define Zero(v) memset((v), 0, sizeof(v))


typedef int m_t;
const int MRows = 2*MAXN;
const int MCols = 2*MAXN;
struct Matrix {
    int r, c;
    m_t m[MRows][MCols];
    void init(int R, int C) { Zero(m); r=R; c=C; }
    void iden() {
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                m[i][j] = i == j ? 1 : 0;
    }
    void print() {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) printf("%4d  ", m[i][j]);
            printf("\n");
        }
    }

    void mul(const Matrix &y, Matrix &z) const {
        z.r = r, z.c = y.c; m_t v;
        for (int i = 0; i < z.r; ++i)
            for (int j = 0; j < z.c; ++j) {
                v = 0;
                for (int k = 0; k < c; ++k)
                    v += m[i][k] * y.m[k][j];
                z.m[i][j] = v % 10;
            }
    }

    void exp(int e, Matrix &z) {
        z.init(r, c); z.iden();
        Matrix x, b = *this;
        while (true) {
            if (e & 1) { z.mul(b, x); z = x; }
            e >>= 1;
            if (e == 0) break;
            b.mul(b, x);
            b = x;
        }
    }
};


int n, k;
Matrix A, B, C, Ae;


void solve()
{
    if (k == 1) {
        C.init(n, 2*n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                C.m[i][j] = A.m[i][j];
        return;
    }

    B.init(n, 2*n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            B.m[i][j] = B.m[i + n][j] = A.m[i][j];
            A.m[i][j + n] = A.m[i + n][j + n] = i == j ? 1 : 0;
        }

    A.exp(k - 1, Ae);
    Ae.mul(B, C);
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &n, &k);

        A.init(2*n, 2*n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                scanf("%d", &A.m[i][j]);

        solve();

        printf("Case %d:\n", ++ncase);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                printf("%d", C.m[i][j]);
            putchar('\n');
        }
    }

    return 0;
}

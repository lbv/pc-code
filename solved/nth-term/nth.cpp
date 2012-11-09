#include <cstdio>
#include <cstring>


#define MOD 10007

#define Zero(v) memset((v), 0, sizeof(v))


//
// Matrix Exponentiation
//
typedef int m_t;
const int MRows = 4;
const int MCols = 4;
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
                z.m[i][j] = v % MOD;
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


int n, a, b, c;


int solve()
{
    if (n <= 2) return 0;

    Matrix A;
    A.init(4, 4);
    A.m[0][0] = a;
    A.m[0][2] = b;
    A.m[0][3] = c;
    A.m[1][0] = 1;
    A.m[2][1] = 1;
    A.m[3][3] = 1;

    Matrix R;
    A.exp(n - 2, R);

    return R.m[0][3];
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d%d", &n, &a, &b, &c);
        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}

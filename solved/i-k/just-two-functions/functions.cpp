#include <cstdio>
#include <cstring>


#define Zero(v) memset((v), 0, sizeof(v))


typedef long long i64;


const int MAX_ROWS = 6;
const int MAX_COLS = 6;


i64 M;


#include <iostream>
template <typename T>
struct Matrix {
    int r, c;
    T m[MAX_ROWS][MAX_COLS];
    Matrix(int R, int C) : r(R), c(C) {}

    void init(T *v) {
        for (int i = 0, p = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                m[i][j] = v[p++];
    }
    void iden() {
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                m[i][j] = i == j ? 1 : 0;
    }
    void print() {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) std::cout << m[i][j] << " ";
            puts("");
        }
    }

    T x[MAX_ROWS][MAX_COLS];
    Matrix &operator*=(const Matrix &y) {
        Zero(x);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j) {
                T v = 0;
                for (int k = 0; k < c; ++k)
                    v += m[i][k] * y.m[k][j];
                x[i][j] = v % M;
            }
        memcpy(m, x, sizeof(m)); return *this;
    }
};

template<typename TB, typename TE>
void sq_pow(TB b, TE e, TB &r) {
    for (; e; e >>= 1, b *= b) if (e & 1) r *= b;
}


int a1, b1, c1, a2, b2, c2;
int f0, f1, f2, g0, g1, g2;
int q, n;
int fn, gn;

Matrix<i64> O(6, 6);
Matrix<i64> R(6, 6);


void init_matrix()
{
    i64 vals[] = {
        a1, b1,  0,  0,  0, c1,
         1,  0,  0,  0,  0,  0,
         0,  1,  0,  0,  0,  0,
         0,  0, c2, a2, b2,  0,
         0,  0,  0,  1,  0,  0,
         0,  0,  0,  0,  1,  0
    };
    O.init(vals);
}

void query()
{
    if (n == 0) { fn = f0 % M, gn = g0 % M; return; }
    if (n == 1) { fn = f1 % M, gn = g1 % M; return; }
    if (n == 2) { fn = f2 % M, gn = g2 % M; return; }

    Matrix<i64> A = O;
    R.iden();

    sq_pow(A, n - 2, R);
    fn = (R.m[0][0] * f2 + R.m[0][1] * f1 + R.m[0][2] * f0 +
          R.m[0][3] * g2 + R.m[0][4] * g1 + R.m[0][5] * g0) % M;
    gn = (R.m[3][0] * f2 + R.m[3][1] * f1 + R.m[3][2] * f0 +
          R.m[3][3] * g2 + R.m[3][4] * g1 + R.m[3][5] * g0) % M;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d%d%d%d%d%d%d%d%d%d%lld%d",
              &a1, &b1, &c1, &a2, &b2, &c2,
              &f0, &f1, &f2, &g0, &g1, &g2,
              &M, &q);

        printf("Case %d:\n", ++ncase);

        init_matrix();
        while (q--) {
            scanf("%d", &n);
            query();
            printf("%d %d\n", fn, gn);
        }
    }

    return 0;
}

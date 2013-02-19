#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;


#define Zero(v) memset((v), 0, sizeof(v))
#define Abs(x)  fabs(x)

const int MAX_ROWS = 100;
const int MAX_COLS = 101;


template <typename T>
struct Matrix {
    int r, c;
    T m[MAX_ROWS][MAX_COLS];
    Matrix(int R, int C) : r(R), c(C) {}

    bool gaussian() {
        for (int k = 0; k < r; ++k) {
            int im = k; T v=Abs(m[k][k]);
            for (int i = k + 1; i < r; ++i)
                if (Abs(m[i][k]) > v) v = Abs(m[i][k]), im = i;
            if (v == 0) return false;
            swap(m[k], m[im]);
            for (int i = k + 1; i < r; ++i) {
                for (int j = k + 1; j < c; ++j)
                    m[i][j] -= m[k][j] * (m[i][k] / m[k][k]);
                m[i][k] = 0;
            }
        }
        return true;
    }

    T memo[MAX_ROWS];
    bool vis[MAX_ROWS];
    T solve(int i) {
        if (vis[i]) return memo[i];
        T ans = m[i][c - 1] / m[i][i];
        for (int j = i + 1; j < r; ++j)
            if (m[i][j] != 0)
                ans -= solve(j) * m[i][j] / m[i][i];

        vis[i] = true;
        return memo[i] = ans;
    }
};


int n;
int board[100];

Matrix<double> A(100, 101);


double solve()
{
    Zero(A.m);

    for (int i = 0; i < 99; ++i) {
        A.m[i][i] = -1;

        for (int j = 1; j <= 6; ++j) {
            int t = i + j;
            A.m[i][100] -= 1.0 / 6;
            if (t < 100) {
                int tf = board[t];
                A.m[i][tf] += 1.0 / 6;
            }
            else
                A.m[i][i] += 1.0 / 6;
        }
    }
    A.m[99][99] = 1.0;

    A.gaussian();

    Zero(A.vis);
    return A.solve(0);
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < 100; ++i) board[i] = i;
        while (n--) {
            int a, b;
            scanf("%d%d", &a, &b);
            board[a-1] = b-1;
        }

        printf("Case %d: %.8lf\n", ++ncase, solve());
    }

    return 0;
}

//
// Matrix
//
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
            for (int j = 0; j < c; ++j) cout << m[i][j] << " ";
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
                x[i][j] = v;
            }
        memcpy(m, x, sizeof(m)); return *this;
    }

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

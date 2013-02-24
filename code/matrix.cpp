//
// Matrix
//
template <typename T>
struct Matrix {
    int r, c;
    T m[MAX_ROWS][MAX_COLS];
    Matrix(int R, int C) : r(R), c(C) {}

    void clr() { Zero(m); }
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
                x[i][j] = v;
            }
        memcpy(m, x, sizeof(m)); return *this;
    }

    // returns number of free variables
    int gaussian() {
        int fv = 0, nr, p, q;
        for (p=0, q=0; p < r && q < c; ++p, ++q) {
            for (nr = p; nr < r; ++nr) if (m[nr][q] != 0) break;
            if (nr == r) { ++fv; --p; continue; }
            if (nr != p) swap(m[p], m[nr]);
            for (int i = p + 1; i < r; ++i) {
                T fac = m[i][q] / m[p][q];
                for (int j = q + 1; j < c; ++j)
                    m[i][j] -= m[p][j] * fac;
                m[i][q] = 0;
            }
        }
        return fv + c - q;
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

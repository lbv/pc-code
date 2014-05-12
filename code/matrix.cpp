//
// Matrix
//
#define MAX_ROWS MAX_STATES
#define MAX_COLS MAX_STATES
struct Matrix {
	int r, c;
	MatrixT m[MAX_ROWS][MAX_COLS];

	void init(int R, int C) { r = R, c = C; }
	void init(int R, int C, const MatrixT *v) {
		r = R, c = C;
		for (int i = 0, p = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				m[i][j] = v[p++];
	}
	void iden() { Clr(m); for (int i = 0; i < r; ++i) m[i][i] = 1; }
	void print() {
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) printf("%3d ", m[i][j]);
			puts("");
		}
	}

	MatrixT x[MAX_ROWS][MAX_COLS];
	Matrix &operator*=(const Matrix &y) {
		Clr(x);
		for (int i = 0; i < r; ++i)
			for (int k = 0; k < c; ++k)
				if (m[i][k] != 0)
					for (int j = 0; j < c; ++j)
						x[i][j] += m[i][k] * y.m[k][j];
		memcpy(m, x, sizeof(m)); return *this;
	}

	//
	// Gaussian elimination. Returns number of free variables.
	//
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

	MatrixT memo[MAX_ROWS];
	bool vis[MAX_ROWS];
	MatrixT solve(int i) {
		if (vis[i]) return memo[i];
		MatrixT ans = m[i][c - 1] / m[i][i];
		for (int j = i + 1; j < r; ++j)
			if (m[i][j] != 0)
				ans -= solve(j) * m[i][j] / m[i][i];

		vis[i] = true;
		return memo[i] = ans;
	}
};

template<typename T>
void matrix_pow(Matrix &b, T e, Matrix &res) {
	res.init(b.r, b.c);	res.iden(); if (e == 0) return;
	while (true) {
		if (e & 1) res *= b;
		if ((e >>= 1) == 0) break;
		b *= b;
	}
}

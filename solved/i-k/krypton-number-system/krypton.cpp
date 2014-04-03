#include <cstdio>
#include <cstring>


#define Clr(m) memset(m, 0, sizeof(m))


typedef unsigned int u32;
typedef u32 MatrixT;


#define MAX_ROWS 128
#define MAX_COLS 128
struct Matrix {
	int r, c;
	MatrixT m[MAX_ROWS][MAX_COLS];

	void init(int R, int C) { r = R, c = C; }
	void init(int R, int C, MatrixT *v) {
		r = R, c = C;
		for (int i = 0, p = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				m[i][j] = v[p++];
	}
	void iden() { Clr(m); for (int i = 0; i < r; ++i) m[i][i] = 1; }

	MatrixT x[MAX_ROWS][MAX_COLS];
	Matrix &operator*=(const Matrix &y) {
		Clr(x);
		for (int i = 0; i < r; ++i)
			for (int k = 0; k < c; ++k)
				for (int j = 0; j < c; ++j)
					x[i][j] += m[i][k] * y.m[k][j];
		memcpy(m, x, sizeof(m)); return *this;
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


int base, score;
Matrix A, P;

int sq[25 + 1];  // sq[i]: the square root of i if it's a round int, or 0


u32 solve()
{
	int rows = base;

	Clr(A.m);
	for (int i = 0; i < base; ++i) {
		if (i > 0) A.m[i][i-1] = 1;
		if (i < base - 1) A.m[i][i+1] = 1;

		// edges to lower digits
		int u = i;
		for (int j = 1, J = i*i; j < J; ++j) {
			int v = rows++;
			A.m[u][v] = 1;

			if (sq[j + 1] > 0)
				A.m[v][ i - sq[j+1] ] = 1;

			u = v;
		}

		// edges to higher digits
		u = i;
		for (int j = 1, J = (base-1-i)*(base-1-i); j < J; ++j) {
			int v = rows++;
			A.m[u][v] = 1;

			if (sq[j + 1] > 0)
				A.m[v][ i + sq[j+1] ] = 1;

			u = v;
		}
	}

	A.init(rows, rows);
	matrix_pow(A, score, P);

	u32 ans = 0;
	for (int i = 1; i < base; ++i)
		for (int j = 0; j < base; ++j)
			ans += P.m[i][j];

	return ans;
}

void prepare()
{
	for (int i = 1; i <= 5; ++i)
		sq[i*i] = i;
}

int main()
{
	prepare();

	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &base, &score);
		printf("Case %d: %u\n", ++ncase, solve());
	}

	return 0;
}

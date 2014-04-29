#include <cstdio>
#include <cstring>


#define MAXLEN 50

#define Clr(m) memset(m, 0, sizeof(m))

const int MAX_STATES = MAXLEN + 1;


typedef unsigned int u32;
typedef u32 MatrixT;


//
// Knuth-Morris-Pratt
//
#define MAXW MAXLEN
struct KMP {
	int T[MAXW + 1];
	void init(const char *W, int lw) {
		T[0] = -1, T[1] = 0;
		for (int p = 2, c = 0; p < lw;) {
			if (W[p-1] == W[c]) T[p++] = ++c;
			else if (c > 0) c = T[c];
			else T[p++] = 0;
		}
	}
};

//
// Matrix
//
#define MAX_ROWS MAX_STATES
#define MAX_COLS MAX_STATES
struct Matrix {
	int r, c;
	MatrixT m[MAX_ROWS][MAX_COLS];

	void init(int R, int C) { r = R, c = C; }
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


int n;
char A[27];
char S[MAXLEN + 1];

Matrix M, R;

bool used[26];
KMP kmp;


u32 solve()
{
	int la = strlen(A);
	int ls = strlen(S);
	M.init(ls + 1, ls + 1);
	Clr(M.m);

	M.m[ls][ls] = la - 1;
	M.m[ls][0] = 1;

	kmp.init(S, ls);

	for (int i = 1; i < ls; ++i) {
		Clr(used);
		int cnt = 0;

		for (int j = i; j >= 0; j = kmp.T[j])
			if (! used[S[j] - 'a']) {
				used[S[j] - 'a'] = true;
				++cnt;
				++M.m[i-1][j];
			}
		M.m[i-1][ls] = la - cnt;
	}

	matrix_pow(M, n, R);

	u32 ans = 0;
	for (int i = 0; i <= ls; ++i)
		ans += R.m[ls][i];
	ans -= R.m[ls][ls-1];

	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%s%s", &n, A, S);
		printf("Case %d: %u\n", ++ncase, solve());
	}

	return 0;
}
